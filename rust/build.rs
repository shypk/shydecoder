// build.rs
extern crate cc;

fn main() {
    // Define paths
    let c_dir = "../src";
    
    let mut build = cc::Build::new();

    // Add all .c
    build.files(glob::glob(&format!("{}/*.c", c_dir))
        .expect("Failed to read glob pattern")
        .filter_map(Result::ok)
        .collect::<Vec<_>>());

    build.include("../include");
    build.compile("libshydecoder.a");

    // Tell Cargo to link to the static library
    println!("cargo:rerun-if-changed={}", c_dir);
    println!("cargo:rustc-link-lib=static=shydecoder");
}
