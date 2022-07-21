
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>  
#include <search.h>

static char *companies[] = { "Intel", "AMD", "ARM", "Apple",
                            "Marvell", "Qualcomm", "IBM", "Nvidia" };

static char *uarch[] = { "Willow Cove", "Zen 3", "A78", "A14",
                            "ThunderX2", "Kryo", "z15", "Ampere" };

#define PORT 8765

main()
{
    int    i;
    int    fd1, fd2;
    struct sockaddr_in    saddr;
    struct sockaddr_in    caddr;
    int    len;
    int    ret;
    ENTRY e;
    ENTRY *ep;
    char *buf[1024];
    char *ans[1024];

    const size_t capacity = sizeof companies / sizeof companies[0];
    hcreate(capacity);
   
    for (size_t i = 0; i < capacity - 2; i++) {
       e.key = companies[i];
       e.data = (void *) uarch[i];

       ep = hsearch(e, ENTER);

       if (ep == NULL) {
           fprintf(stderr, "entry failed\n");
           exit(EXIT_FAILURE);
       }
   }


    if ((fd1 = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket");
      exit(1);
    }

    bzero((char *)&saddr, sizeof(saddr));

    saddr.sin_family      = PF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port        = htons(PORT);

    if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
      perror("bind");
      exit(1);
    }
    

    if (listen(fd1, 1) < 0) {
      perror("listen");
      exit(1);
    }

    len = sizeof(caddr);

    if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, &len)) < 0) {
		perror("accept");
		exit(1);
    }
    close(fd1);

    do{
        ret = read(fd2, buf, 1024);


        e.key = buf;
        ep = hsearch(e, FIND);
        //printf("%s -> %s\n", e.key, (char*)ep->data);
        ans = (char*)ep->data;

        write(fd2, ans, 1024);
    }
    while (strcmp(buf, "QUIT\n") != 0);


    close(fd2);
}
