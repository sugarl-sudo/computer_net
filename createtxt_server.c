/*
 * server.c
 *   クライアントからの接続要求を受け付けるサーバープログラム。
 *   
 *   クライアントから送られてきた文字列を大文字に変換して送り返す。
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>  /* #include <sys/un.h>の代わり */


#define PORT 8765

main()
{
    int    i;
    int    fd1, fd2;
    struct sockaddr_in    saddr;
    struct sockaddr_in    caddr;
    int    len;
    int    ret;
    char   buf[1024];
    FILE *fp;

    fp = fopen("phone_book.txt", "w");

    /*
     *  ストリーム型ソケット作る．
     */
    if ((fd1 = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket");
      exit(1);
    }

    /* 
     * saddrの中身を0にしておかないと、bind()でエラーが起こることがある
     */
    bzero((char *)&saddr, sizeof(saddr));

    /*
     * ソケットの名前を入れておく
     */
    saddr.sin_family      = PF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port        = htons(PORT);

    /*
     * ソケットにアドレスをバインドする。
     */
    if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
      perror("bind");
      exit(1);
    }
    
    /*
     * listenをソケットに対して発行する
     */
    if (listen(fd1, 1) < 0) {
      perror("listen");
      exit(1);
    }

    len = sizeof(caddr);
    /*
     * accept()により、クライアントからの接続要求を受け付ける。
     * 成功すると、クライアントと接続されたソケットのディスクリプタが
     * fd2に返される。このfd2を通して通信が可能となる。
     * fd1は必要なくなるので、close()で閉じる。
     */
    if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, &len)) < 0) {
		perror("accept");
		exit(1);
    }
    close(fd1);

    /* クライアントと接続されているソケットからデータを受け取る */

    do{
        ret = read(fd2, buf, 1024);

        fprintf(fp, buf, "w");
        fprintf(fp, "\n", "w");  

        /* 変換したデータをクライアントに送り返す */
        write(fd2, buf, 1024);
    }
    while (strcmp(buf, "QUIT\n") != 0);

    /* 通信が終わったらソケットを閉じる */
    close(fd2);
}
