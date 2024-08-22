use crate::ffi::*;

use std::ffi::{CString, CStr};
use std::os::raw::c_char;
use std::os::raw::{c_int};


pub fn shy_swap(a: *mut c_int, b: *mut c_int) {
    unsafe { swap(a, b) }  
}

pub fn shy_unify_decode(target: &str, level: i32 ) -> String  {
    let c_input = CString::new(target).expect("CString::new failed");
    let mut output_buffer = vec![0; target.len() + 1];
    
    unsafe {
        unify_decode(c_input.as_ptr(), level, output_buffer.as_mut_ptr() as *mut c_char );
    }

    let c_output = unsafe { CStr::from_ptr(output_buffer.as_ptr() as *const c_char) };
    c_output.to_string_lossy().into_owned()

}

