reference：
http://blog.chinaunix.net/uid-393131-id-2409972.html
http://redmine.lighttpd.net/projects/lighttpd/wiki/Docs_ModFastCGI

vi lighttpd.conf
1.添加允许执行的FastCGI扩展名
static-file.exclude-extensions = ( ".php", ".pl", ".fcgi" , ".cgi", "fastcgi")

2.增加Lighttpd能够解析FastCGI服务的语句
fastcgi.server            = (
> "/test" => (
> > "test.fastcgi.handler" => (

> "socket" => "/tmp/test.fastcgi.socket",
> "check-local" => "disable",
> "bin-path" => "/data/www/webroot/cgi-bin/test.fastcgi",
> "min-procs" => 1,
> "max-procs" => 30,
> "idle-timeout" => 30
> > )
> > )
> > > )
3.编写C的FastCGI
// gcc -I/usr/include/fastcgi -lfcgi testfastcgi.c -o test.fastcgi
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <alloca.h>
#include <fcgiapp.h>
#define LISTENSOCK\_FILENO 0
#define LISTENSOCK\_FLAGS 0
int main(int argc, char argv) {

> openlog ("testfastcgi", LOG\_CONS|LOG\_NDELAY, LOG\_USER);
> int err = FCGX\_Init (); /**call before Accept in multithreaded apps**/
> if (err) { syslog (LOG\_INFO, "FCGX\_Init failed: %d", err); return 1; }
> FCGX\_Request cgi;
> err = FCGX\_InitRequest(&cgi, LISTENSOCK\_FILENO, LISTENSOCK\_FLAGS);
> if (err) { syslog (LOG\_INFO, "FCGX\_InitRequest failed: %d", err); return 2; }
> while (1) {
> > err = FCGX\_Accept\_r(&cgi);
> > if (err) { syslog (LOG\_INFO, "FCGX\_Accept\_r stopped: %d", err); break; }
> > char envp;
> > int size = 200;
> > for (envp = cgi.envp; **envp; ++envp) size += strlen(**envp) + 11;
> > char**result = (char**) alloca(size);
> > strcpy (result, "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
> > strcat (result, "

&lt;html&gt;



&lt;head&gt;



&lt;title&gt;

testcgi

&lt;/title&gt;



&lt;/head&gt;



&lt;body&gt;

<ul>\r\n");<br>
<blockquote>for (envp = cgi.envp; <b>envp; ++envp) {<br>
<blockquote>strcat(result, "</b><li>");<br>
strcat(result, **envp);<br>
strcat(result, "</li>\r\n");<br>
</blockquote>}<br>
strcat(result, "</ul>

</body>

<br>
<br>
</html><br>
<br>
\r\n");<br>
FCGX_PutStr(result, strlen(result), cgi.out);<br>
FCGX_Finish_r(&cgi);<br>
</blockquote>
> }
> FCGX\_ShutdownPending();
> return 0;
}
4.编译并运行
gcc -I/usr/include/fastcgi -lfcgi testfastcgi.c -o test.fastcgi
在IE中输入:
http://test.eoa.kdn:8080/test
如果成功,即可看到如下信息:
FCGI\_ROLE=RESPONDER
SERVER\_SOFTWARE=lighttpd/1.4.22
SERVER\_NAME=test.eoa.kdn:8080
GATEWAY\_INTERFACE=CGI/1.1
SERVER\_PORT=8080
SERVER\_ADDR=102.108.15.119
REMOTE\_PORT=16977
REMOTE\_ADDR=61.135.159.208
SCRIPT\_NAME=/test
PATH\_INFO=
SCRIPT\_FILENAME=/data/www/webroot/test
DOCUMENT\_ROOT=/data/www/webroot
REQUEST\_URI=/test
QUERY\_STRING=
REQUEST\_METHOD=GET
REDIRECT\_STATUS=200
SERVER\_PROTOCOL=HTTP/1.1
HTTP\_ACCEPT=**/**HTTP\_ACCEPT\_LANGUAGE=zh-cn
HTTP\_ACCEPT\_ENCODING=gzip, deflate
HTTP\_USER\_AGENT=Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Maxthon)
HTTP\_HOST=202.108.15.19:8080
HTTP\_CONNECTION=Keep-Alive**

参考文章:
http://redmine.lighttpd.net/wiki/1/Docs:ModFastCGI#FastCGI-and-Programming-Languages