# R Boost Beast Example

Example code for setting up R packages with [Boost Beast](https://github.com/boostorg/beast), Rcpp and [`later`](https://github.com/r-lib/later).

Includes modified Boost Beast examples for asynchronous servers using multiple `later` background tasks as workers. 

* HTTP (`beast/example/http/server/async/`)
* Websocket (`beast/example/websocket/server/async/`) 


## Info

Required Boost headers missing from BH and AsioHeaders:

* asio/coroutine.h
* asio/unyield.h
* asio/yield.h
* core/exchange.h
* make_unique.h

Building:

* `DESCRIPTION` contains all needed dependancies.
* `src/Makevars(.win)` contains needed compiler flags.

## License

Boost Beast and all other dependencies specify their respective licenses. Use the rest of this code however you want (MIT license). It was quite a bit of work to figure out how to get this running, so it would be nice if you decide credit me.