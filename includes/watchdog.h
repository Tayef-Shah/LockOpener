#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/watchdog.h>
#include <sys/ioctl.h>

#include "constants.h"
#include "log.h"

const int DEFAULT_WATCHDOG = 10;

int initWatchDog(int timer) {
	int fd = open("/dev/watchdog", O_WRONLY);

	// Set Timeout and enable 
	int wdTimeout = timer;
	if (timer < 0)
		wdTimeout = DEFAULT_WATCHDOG;
	int options = WDIOS_ENABLECARD;
	ioctl(fd, WDIOC_SETOPTIONS, &options);
	ioctl(fd, WDIOC_SETTIMEOUT, &wdTimeout);

	// Get Timeout
	int timeout = -1; 
	ioctl(fd, WDIOC_GETTIMEOUT, &timeout);

	// Log Watchdog
	char buffer[128];
	snprintf(buffer, 128, "Watchdog has been enabled with timeout %d seconds.", timeout);
	writeLog(lockOpener.logFile, lockOpener.name, INFO, buffer);

	return fd;
}

void* pingWatchDog(void *vargp) {
	while (1) {
		ioctl(lockOpener.watchDog, WDIOC_KEEPALIVE, 0);
		usleep(1000000);
	}
}

void stopWatchDog() {
	// Log Watchdog 
	char buffer[128];
	snprintf(buffer, 128, "Watchdog has been disabled.");
	writeLog(lockOpener.logFile, lockOpener.name, INFO, buffer);

	int options = WDIOS_DISABLECARD;
	ioctl(lockOpener.watchDog, WDIOC_SETOPTIONS, &options);
	close(lockOpener.watchDog);
}

#endif