# LockOpener
##### ECE 150 Self Directed Project

### Log and DB Files after Demo Run
The log and database files after the demo run can be found in the `/demo` directory.
Additionally, the service file used by `systemd` to run the `LockOpener` binary can also be found in the `/demo` directory.

### Permissions on the Raspberry Pi
- Both the compiled binary and the debug binary needs to marked as executable
```
chmod +x builds/debug && chmod +x LockOpener
```
- The website directory needs to owned by www-data (ie. the apache process)
```
chown -R www-data:www-data site
```
- The database needs to be writeable and readable as if it was a log file
```
chmod 777 site/database/db.db3
```
- The program itself needs to run on elevated permissions (ie. sudo)
```
sudo ./LockOpener
OR
sudo ./builds/debug
```

### Restart Fix
When restarting with `sudo reboot` the system may hang at shutdown, should that occur the following commands will forcefully reboot the Rasberry Pi
```
echo s > /proc/sysrq-trigger &&
echo u > /proc/sysrq-trigger &&
echo b > /proc/sysrq-trigger
```