// [[Rcpp::plugins("cpp11")]]

#include "http_server_async.h"
#include <Rcpp.h>
#include <later_api.h>

namespace rbeast
{
    namespace ht
    {
        class HttpServerAsyncTask : public later::BackgroundTask
        {
        public:
            HttpServerAsyncTask(const std::string &t_host, unsigned short t_port, int t_threads)
                : taskid(0), host(t_host), port(t_port), threads(t_threads)
            {
            }
            HttpServerAsyncTask(int t_taskid, net::io_context *t_pioc)
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
                std::make_shared<listener>(
                    ioc,
                    tcp::endpoint{address, (unsigned short)port},
                    doc_root)
                    ->run();

                // Start other processes
                for (auto i = 1; i < threads; i++)
                {
                    (new HttpServerAsyncTask(i, &ioc))->begin();
                }
                ioc.run();
            }

            void complete()
            {
                Rcpp::Rcout << "Task " << taskid << " stopped.\n";
                if (taskid == 0)
                    Rcpp::Rcout << "Server stopped.\n";
            }

        private:
            int taskid;
            std::string host;
            unsigned short port;
            int threads;
            net::io_context *pioc;
        };

        HttpServerAsyncTask *server = nullptr;
    } // namespace ht
} // namespace rbeast

//' @export
// [[Rcpp::export]]
void beast_http_server_async(std::string host = "127.0.0.1", int port = 1234, int threads = 4)
{
    if (rbeast::ht::server == nullptr)
    {
        rbeast::ht::server = new rbeast::ht::HttpServerAsyncTask(host, port, threads);
        rbeast::ht::server->begin();

        Rcpp::Rcout << "Server started: http://" << host.c_str() << ":" << port << "/\n";
    }
    else
    {
        Rcpp::Rcout << "Server already running, call beast_http_async_stop()";
    }
}

//' @export
// [[Rcpp::export]]
void beast_http_server_async_stop()
{
    if (rbeast::ht::server != nullptr)
    {
        rbeast::ht::server->end();
    }
}