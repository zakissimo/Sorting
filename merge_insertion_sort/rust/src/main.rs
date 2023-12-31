// https://en.wikipedia.org/wiki/Merge-insertion_sort

use rand::Rng;
use std::collections::{HashMap, VecDeque};
use std::env;
use std::time::Instant;

fn is_sorted(vec: &Vec<i32>) {
    for i in 1..vec.len() {
        if i < vec.len() - 1 && vec[i - 1] > vec[i] {
            panic!("Vector is NOT sorted! at idx {}", i);
        }
    }
    println!("Vector is sorted!");
}

fn bs(vec: &Vec<i32>, mut start: usize, mut end: usize, target: i32) -> usize {
    while start <= end {
        let mid = (end + start) / 2;
        if vec[mid] < target {
            start = mid + 1;
        } else if mid != 0 && vec[mid] > target {
            end = mid - 1;
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

    let mut max_to_min: HashMap<i32, VecDeque<i32>> = HashMap::with_capacity(vec.len() / 2);
    let mut maxs: Vec<i32> = Vec::with_capacity(vec.len() / 2);

    for pair in vec.chunks(2) {
        if pair.len() == 2 {
            let min = pair[0].min(pair[1]);
            let max = pair[0].max(pair[1]);
            max_to_min
                .entry(max)
                .or_insert(VecDeque::new())
                .push_back(min);
            maxs.push(max);
        }
    }

    let maxs = merge_insertion_sort(&maxs);

    let mut s: Vec<i32> = Vec::with_capacity(vec.len());

    s.push(
        max_to_min
            .get_mut(&maxs[0])
            .expect("Key should be in map")
            .pop_front()
            .expect("Deque shouldn't be empty"),
    );
    for i in 0..maxs.len() {
        s.push(maxs[i]);
    }

    let mut p: usize = 0;
    let mut n: usize = 2;

    for (chunk_idx, chunk) in maxs.chunks(n).enumerate() {
        let start_idx = if chunk_idx == 0 { 1 } else { 0 };
        for i in (start_idx..chunk.len()).rev() {
            let max_pos = bs(&s, i + 1, s.len() - 1, chunk[i]);
            let min = max_to_min
                .get_mut(&chunk[i])
                .expect("Key should be in map")
                .pop_front()
                .expect("Deque shouldn't be empty");
            let idx = bs(&s, 0, max_pos - 1, min);
            s.insert(idx, min);
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
    (0..size).map(|_| rng.gen_range(1..=3000)).collect()
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let mut vec;
    vec = if args.len() == 1 {
        generate_random_vector(3000)
    } else if args.len() == 2 {
        args[1]
            .split_whitespace()
            .map(|s| s.parse::<i32>())
            .collect::<Result<Vec<i32>, _>>()
            .expect("Input to be i32 seq")
    } else {
        args[1..]
            .iter()
            .map(|s| s.parse::<i32>())
            .collect::<Result<Vec<i32>, _>>()
            .expect("Input to be i32 seq")
    };
    let mut vec_copy = vec.clone();

    let start_time = Instant::now();
    let _sorted_vec = merge_insertion_sort(&mut vec);
    let end_time = Instant::now();

    is_sorted(&_sorted_vec);

    let elapsed_time = end_time.duration_since(start_time);

    println!(
        "Vector of {} elements was sorted in {:?} (Rust - Merge Insertion Sort)",
        _sorted_vec.len(),
        elapsed_time
    );

    let start_time = Instant::now();
    vec_copy.sort();
    let end_time = Instant::now();

    let elapsed_time = end_time.duration_since(start_time);

    println!(
        "Vector of {} elements was sorted in {:?} (Rust - Builtin .sort())",
        vec_copy.len(),
        elapsed_time
    );
}
