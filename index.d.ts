// Copyright 2015 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

export var Process: number;
export var Pgrp: number;
export var User: number;

export function getpriority(which: number, who: number, cb: (err: any, prio: number) => void): void;
export function setpriority(which: number, who: number, prio: number, cb: (err: any) => void): void;
