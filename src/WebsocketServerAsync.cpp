// [[Rcpp::plugins("cpp11")]]

#include "ws_server_async.h"
#include <Rcpp.h>
#include <later_api.h>

namespace rbeast
{
    namespace ws
    {
        class WebsocketServerAsyncTask : public later::BackgroundTask
        {
        public:
            WebsocketServerAsyncTask(const std::string &t_host, unsigned short t_port, int t_threads)
                : taskid(0), host(t_host), port(t_port), threads(t_threads)
            {
            }
            WebsocketServerAsyncTask(int t_taskid, net::io_context *t_pioc)
                : taskid(t_taskid), pioc(t_pioc)
            {
            }

            void end()
            {
                pioc->stop();
            }

        protected:
            void execute()
            {
                if (taskid != 0) // Child process
                {
                    pioc->run();
                    return;
                }

                auto const address = net::ip::make_address(host);
                auto const doc_root = std::make_shared<std::string>(".");

                // The io_context is required for all I/O
                net::io_context ioc{std::max<int>(1, threads)};
                //net::io_context ioc{1};
                pioc = &ioc;

                // Create and launch a listening port
                std::make_shared<listener>(ioc, tcp::endpoint{address, port})->run();

                // Start other processes
                for (auto i = 1; i < threads; i++)
                {
                    (new WebsocketServerAsyncTask(i, &ioc))->begin();
                }
                ioc.run();
            }

            void complete()
            {
                Rcpp::Rcout << "WS Task " << taskid << " stopped.\n";
                if (taskid == 0)
                    Rcpp::Rcout << "WS Server stopped.\n";
            }

        private:
            int taskid;
            std::string host;
            unsigned short port;
            int threads;
            net::io_context *pioc;
        };

        WebsocketServerAsyncTask *ws_server = nullptr;
    } // namespace ws
} // namespace rbeast

//' @export
// [[Rcpp::export]]
void beast_websocket_server_async(std::string host = "127.0.0.1", int port = 1234, int threads = 4)
{
    if (rbeast::ws::ws_server == nullptr)
    {
        rbeast::ws::ws_server = new rbeast::ws::WebsocketServerAsyncTask(host, port, threads);
        rbeast::ws::ws_server->begin();

        Rcpp::Rcout << "WS Server started: ws://" << host.c_str() << ":" << port << "/\n";
    }
    else
    {
        Rcpp::Rcout << "WS Server already running, call beast_http_async_stop()";
    }
}

//' @export
// [[Rcpp::export]]
void beast_websocket_server_async_stop()
{
    if (rbeast::ws::ws_server != nullptr)
    {
        rbeast::ws::ws_server->end();
    }
}