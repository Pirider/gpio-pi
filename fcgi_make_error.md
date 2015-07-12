referce:http://qichunren.iteye.com/blog/609351

error:
fcgio.cpp:50: error: 'EOF' was not declared in this scope
fcgio.cpp: In member function 'virtual int fcgi\_streambuf::overflow(int)':
fcgio.cpp:70: error: 'EOF' was not declared in this scope
fcgio.cpp:75: error: 'EOF' was not declared in this scope


solution:
/include/fcgio.h add #include 

&lt;cstdio&gt;

