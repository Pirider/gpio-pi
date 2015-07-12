参考：http://blog.csdn.net/liang890319/article/details/8643069


下载安装包，解压，编译，安装：


mkdir temp
cd temp
wget http://project-downloads.drogon.net/files/wiringPi.tgz
tar xf wiringPi.tgz
cd wiringPi/wiringPi/
make
make install



③下面写程序测试：


// led.c

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc,char**argv[.md](.md))
{
> if (argc < 2) {
> > printf("Usage example: ./led 4 \n");
> > return 1;

> }
> int pinNumber = atoi(argv[1](1.md));**

> if (-1 == wiringPiSetup()) {
> > printf("Setup wiringPi failed!");
> > return 1;

> }

> pinMode(pinNumber, OUTPUT); // set mode to output
> while(1) {
> > digitalWrite(pinNumber, 1); // output a high level
> > delay(800);
> > digitalWrite(pinNumber, 0); // output a low level
> > delay(800);

> }

> return 0;
}



编译程序：

gcc led.c -o led -lwiringPi


运行程序：
Run the program:

./led 4

可以看到LED开始闪烁了

可能遇见的问题：

GPIO测试编译时出现了这个问题

/usr/lib/gcc/arm-linux-gnueabi/4.6/http://www.cnblogs.com/../libwiringPi.so:undefined reference to `i2c\_smbus\_write\_byte'
/usr/lib/gcc/arm-linux-gnueabi/4.6/http://www.cnblogs.com/../libwiringPi.so:undefined reference to `i2c\_smbus\_read\_byte'
/usr/lib/gcc/arm-linux-gnueabi/4.6/http://www.cnblogs.com/../libwiringPi.so:undefined reference to `i2c\_smbus\_write\_byte\_data'
/usr/lib/gcc/arm-linux-gnueabi/4.6/http://www.cnblogs.com/../libwiringPi.so:undefined reference to `i2c\_smbus\_write\_word\_data'
/usr/lib/gcc/arm-linux-gnueabi/4.6/http://www.cnblogs.com/../libwiringPi.so:undefined reference to `i2c\_smbus\_read\_word\_data'
/usr/lib/gcc/arm-linux-gnueabi/4.6/http://www.cnblogs.com/../libwiringPi.so:undefined reference to `i2c\_smbus\_read\_byte\_data'
collect2: ld returned 1 exit status



官方论坛上说是少装了库的原因

安装这几个库： i2c-tools，libi2c-dev ，python-smbus

安装参考 sudo apt-get install libi2c-dev

然后重新

make clean

sudo make uninstall



make

sudo make install

重新编译下你的.c文件

gcc led.c -o led -lwiringPi

sudo ./led 4

虽然输入的是4

实际上是GPIO23不停输出高低电平