// Copyright 2015 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

var priority = require('../');
var assert = require('assert');


describe('priority extension', function() {
    it('should call getpriority', function(done) {
        priority.get(priority.Process, 0, function(err, prio) {
            assert.equal(err, undefined);
            assert.equal(prio, 0);
            done();
        });
    });
    it('should call setpriority', function(done) {
        priority.set(priority.Process, 0, 10, function(err) {
            assert.equal(err, undefined);

            priority.get(priority.Process, 0, function(err, prio) {
                assert.equal(err, undefined);
                assert.equal(prio, 10);
                done();
            });
        });
    });
});
