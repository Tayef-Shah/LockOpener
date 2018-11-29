# LockOpener
ECE 150 Self Directed Project

### Raspberry Pi Command
sudo chown -R pi:pi * && git reset --hard HEAD && git pull && chmod +x builds/debug && sudo chown -R www-data:www-data site && sudo chmod 777 site/database/db.db3 && sudo ./builds/debug

root@LockOpener:/home/pi# echo s > /proc/sysrq-trigger
root@LockOpener:/home/pi# echo u > /proc/sysrq-trigger
root@LockOpener:/home/pi# echo b > /proc/sysrq-trigger

### PC Command
./compile.sh && ./push.sh "comment"