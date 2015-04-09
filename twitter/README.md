# twitter
実行すると余接の状態をTwitterにポストする．`Twitter twitter()` 内のトークンは認証したアカウントごとに適宜変更する．

## 必要なもの
- Arduino
- 圧力センサ FSR 402
- ブレッドボードとジャンパ線
- 抵抗 330kΩくらい

## 動作仕様
事前に[Tweet Library](https://arduino-tweet.appspot.com/)と[Time Library](http://playground.arduino.cc/code/time)をインストールしておく必要がある．また，Tweet Libraryと任意のTwitterアカウントと紐付けてトークンを取得する必要がある．

回路図はtw_image.pngのとおり．圧力センサは余接の台座に貼り付ける．
