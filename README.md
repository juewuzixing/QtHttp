# QtHttp
## There is a problem occurred:
qt.network.ssl: QSslSocket: cannot call unresolved function SSLv23_client_method

qt.network.ssl: QSslSocket: cannot call unresolved function SSL_CTX_new

qt.network.ssl: QSslSocket: cannot call unresolved function SSL_library_init

qt.network.ssl: QSslSocket: cannot call unresolved function ERR_get_error

qt.network.ssl: QSslSocket: cannot call unresolved function ERR_get_error
## The simple solution is:
Copy the libeay32.dll and ssleay32.dll files from the Qt installation direction to application's exe directory. 

e.g. D:\Qt\Qt5.10.1\Tools\QtCreator\bin
