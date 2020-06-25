#ifndef RBEAST_WS_SERVER_ASYNC_H
#define RBEAST_WS_SERVER_ASYNC_H

#include <boost/beast/core.hpp>

namespace rbeast
{
    namespace ws
    {

        namespace beast = boost::beast;   // from <boost/beast.hpp>
        namespace net = boost::asio;      // from <boost/asio.hpp>
        using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

        // Accepts incoming connections and launches the sessions
        class listener : public std::enable_shared_from_this<listener>
        {
            net::io_context &ioc_;
            tcp::acceptor acceptor_;

        public:
            listener(
                net::io_context &ioc,
                tcp::endpoint endpoint);

            // Start accepting incoming connections
            void
            run();

        private:
            void
            do_accept();

            void
            on_accept(beast::error_code ec, tcp::socket socket);
        };
    } // namespace ws

} // namespace rbeast

#endif