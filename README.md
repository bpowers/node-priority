# node-priority

[![Build Status](https://travis-ci.org/bpowers/node-priority.svg)](https://travis-ci.org/bpowers/node-priority)

This package provides access to the
[`getpriority(2)`](http://man7.org/linux/man-pages/man2/getpriority.2.html)
and
[`setpriority(2)`](http://man7.org/linux/man-pages/man2/setpriority.2.html)
system calls available on OSX, Linux and other UNIX variants.  This
can be used, for example, to implement the UNIX
[`nice(1)`](http://man7.org/linux/man-pages/man1/nice.1.html) utility.

## Usage

```javascript
var priority = require('node-priority');
var getpriority = priority.get;
var setpriority = priority.set;

setpriority(priority.Process, 0, 10, function(err) {
    if (err)
        throw err;
    getpriority(priority.Process, 0, function(err, prio) {
        console.log('successfully set priority to ' + prio);
    });
});

setpriority(function(err, rfd, wfd) {
    if (err) {
        console.log('pipe failed, maybe out of FDs? ' + err);
        return;
    }
    // use rfd and wfd
});
```
