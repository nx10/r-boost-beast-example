// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// beast_http_server_async
void beast_http_server_async(std::string host, int port, int threads);
RcppExport SEXP _rbeast_beast_http_server_async(SEXP hostSEXP, SEXP portSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type host(hostSEXP);
    Rcpp::traits::input_parameter< int >::type port(portSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    beast_http_server_async(host, port, threads);
    return R_NilValue;
END_RCPP
}
// beast_http_server_async_stop
void beast_http_server_async_stop();
RcppExport SEXP _rbeast_beast_http_server_async_stop() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    beast_http_server_async_stop();
    return R_NilValue;
END_RCPP
}
// beast_websocket_server_async
void beast_websocket_server_async(std::string host, int port, int threads);
RcppExport SEXP _rbeast_beast_websocket_server_async(SEXP hostSEXP, SEXP portSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type host(hostSEXP);
    Rcpp::traits::input_parameter< int >::type port(portSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    beast_websocket_server_async(host, port, threads);
    return R_NilValue;
END_RCPP
}
// beast_websocket_server_async_stop
void beast_websocket_server_async_stop();
RcppExport SEXP _rbeast_beast_websocket_server_async_stop() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    beast_websocket_server_async_stop();
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_rbeast_beast_http_server_async", (DL_FUNC) &_rbeast_beast_http_server_async, 3},
    {"_rbeast_beast_http_server_async_stop", (DL_FUNC) &_rbeast_beast_http_server_async_stop, 0},
    {"_rbeast_beast_websocket_server_async", (DL_FUNC) &_rbeast_beast_websocket_server_async, 3},
    {"_rbeast_beast_websocket_server_async_stop", (DL_FUNC) &_rbeast_beast_websocket_server_async_stop, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_rbeast(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
