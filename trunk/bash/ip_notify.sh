#!/bin/bash
#* * * * * /root/gpio-pi/remote_control/bash/ip_notify.sh
    lynx --dump http://ipecho.net/plain > /var/log/ip_notify.txt
    date >> /var/log/ip_notify.txt
    rsync -av --progress --inplace --rsh='ssh -p1234' /var/log/ip_notify.txt root@wangkangle.com:~/ip_notify
    date|xargs -t -I {} echo {}  "success"  >> /var/log/ip_notify.log

exit 0

