// https://en.wikipedia.org/wiki/Merge-insertion_sort

use rand::Rng;
use std::collections::HashMap;
use std::time::Instant;

fn is_sorted(vec: &Vec<i32>) {
    for i in 1..vec.len() {
        if vec[i - 1] > vec[i] {
            panic!("Vector is NOT sorted!");
        }
    }
    println!("Vector is sorted!");
}

fn bs(vec: &Vec<i32>, mut start: usize, mut end: usize, target: i32) -> usize {
    while end > start {
        let mid = (start + end) / 2;
        if vec[mid] > target {
            end = mid;
        } else if vec[mid] < target {
            start = mid + 1;
        } else {
            return mid;
        }
    }
    start
}

fn get_next_jacobsthal_number(p: usize, n: usize) -> usize {
    p * 2 + n
}

fn merge_insertion_sort(vec: &Vec<i32>) -> Vec<i32> {
    if vec.len() == 1 {
        return vec.to_vec();
    }

    let left_over = vec.last().filter(|_| vec.len() % 2 != 0);

    let mut max_to_min: HashMap<i32, i32> = HashMap::with_capacity(vec.len() / 2);
    let mut maxs: Vec<i32> = Vec::with_capacity(vec.len() / 2);

    for pair in vec.chunks(2) {
        if pair.len() == 2 {
            let min = pair[0].min(pair[1]);
            let max = pair[0].max(pair[1]);
            max_to_min.insert(max, min);
            maxs.push(max);
        }
    }

    let maxs = merge_insertion_sort(&maxs);

    let mut s: Vec<i32> = Vec::with_capacity(vec.len());

    for i in 0..maxs.len() {
        if i == 0 {
            s.push(max_to_min[&maxs[i]]);
        }
        s.push(maxs[i]);
    }

    let mut p: usize = 0;
    let mut n: usize = 2;

    for (chunk_idx, chunk) in maxs.chunks(n).enumerate() {
        let start_idx = if chunk_idx == 0 { 1 } else { 0 };
        for i in (start_idx..chunk.len()).rev() {
            let max_pos = bs(&s, i + 1, s.len(), chunk[i]);
            let idx = bs(&s, 0, max_pos, max_to_min[&chunk[i]]);
            s.insert(idx, max_to_min[&chunk[i]]);
        }
        if n < maxs.len() {
            let tmp = n;
            n = get_next_jacobsthal_number(p, n);
            p = tmp;
        }
    }

    if let Some(value) = left_over {
        let idx = bs(&s, 0, s.len() - 1, *value);
        s.insert(idx, *value);
    }

    s
}

fn generate_random_vector(size: usize) -> Vec<i32> {
    let mut rng = rand::thread_rng();
    (0..size).map(|_| rng.gen_range(1..=1000)).collect()
}

fn main() {
    let mut vec = generate_random_vector(3000);
    let mut vec_copy = vec.clone();

    let start_time = Instant::now();
    let _sorted_vec = merge_insertion_sort(&mut vec);
    let end_time = Instant::now();

    is_sorted(&_sorted_vec);

    let elapsed_time = end_time.duration_since(start_time);

    println!(
        "Vector of {} elements was sorted in {:?} (Merge Insertion Sort)",
        vec.len(),
        elapsed_time
    );

    let start_time = Instant::now();
    vec_copy.sort();
    let end_time = Instant::now();

    let elapsed_time = end_time.duration_since(start_time);

    println!(
        "Vector of {} elements was sorted in {:?} (Rust Builtin .sort())",
        vec_copy.len(),
        elapsed_time
    );
}
