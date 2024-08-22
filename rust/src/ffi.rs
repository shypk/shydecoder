
use std::os::raw::{c_int, c_char};

#[link(name = "shydecoder")]
extern "C" {
    pub fn swap( a: *mut c_int, b: *mut c_int  );
    pub fn unify_decode( target: *const c_char, level: i32, ret: *mut c_char) -> bool;
}
