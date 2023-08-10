function include_test(){
    $.ajax({
        url: 'test.html', // リクエストを送信するURLを指定
        async: false, // 非同期リクエストを無効にする
    }).done(function(test_html){ // 通信が成功したら
        document.write(test_html); // herder.htmlを表示する
    });
}