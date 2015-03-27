# webserver_sketch

## 動作
http://192.168.1.177 に接続して，ボタンを押すと9番ピンのHIGH/LOWが変わる．

LEDを接続するとわかりやすい．

クライアントからは以下のようなデータが受信される．

	GET /?1=on HTTP/1.1
	Host: 192.168.1.177
	Connection: keep-alive
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.101 Safari/537.36
	DNT: 1
	Referer: http://192.168.1.177/?1=on
	Accept-Encoding: gzip, deflate, sdch
	Accept-Language: ja,en-US;q=0.8,en;q=0.6

	GET /favicon.ico HTTP/1.1
	Host: 192.168.1.177
	Connection: keep-alive
	Accept: */*
	DNT: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.101 Safari/537.36
	Accept-Encoding: gzip, deflate, sdch
	Accept-Language: ja,en-US;q=0.8,en;q=0.6

`Referer`の ? を読み込んだ時点で `catchGet` はtrueとなり，その直後の数字(1/0)を判定することでOUTPUTのHIGH/LOWを切り替えている