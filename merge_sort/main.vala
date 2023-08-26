// generate random tab with 3000 entities

const uint SIZE = 3000;

int []generate_random_vec(uint size) {
	int []array = {};
	for (int i = 0; i < size; ++i)
	{
		array += Random.int_range(0, 3000);
	}
	return array;
}

// used for compare number with qsort

int compare(int *a, int *b) {
	return (int)(*a > *b);
}

bool test(int []tab) {
	for (int i = 0; i < tab.length - 1; ++i) {
		if (tab[i] > tab[i + 1]) {
			warning("Le tableau n'est pas rangé !!!\n");
			return false;
		}
	}
	return true;
}


void main()
{
	ulong ms;
	var timer = new Timer();
	var array = generate_random_vec(SIZE);
	var array_copy =  array.copy();


	// PART  one  (Array multiple base)
	timer.reset();
	merge_insertion_sort(array, 0, array.length - 1);
	timer.stop();
	timer.elapsed(out ms);
	print(@"GenericTab of $(SIZE) elements was sorted in $(ms) us (vala - Merge Insertion Sort)\n");

	// PART  two (QSort)
	timer.reset();
	Posix.qsort((void*)array_copy, SIZE, 4, compare);
	timer.stop();
	timer.elapsed(out ms);
	print(@"GenericTab of $(SIZE) elements was sorted in $(ms) us (vala - function qsort)\n");

	if (test(array) && test(array_copy))
		print("GenericTab is sorted!\n");
}







///  MATH

void merge_insertion_sort(int[] arr, int left, int right) {
	if (right - left <= 16) {
		for (var i = left + 1; i <= right; ++i) {
			var key = arr[i];
			var j = i - 1;

			while (j >= left && arr[j] > key) {
				arr[j + 1] = arr[j];
				--j;
			}

			arr[j + 1] = key;
		}
	} else {
		var mid = (left + right) / 2;

		merge_insertion_sort(arr, left, mid);
		merge_insertion_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

void merge(int[] arr, int left, int mid, int right) {
	var n1 = mid - left + 1;
	var n2 = right - mid;

	var leftArr = new int[n1]; // no copy only unowned
	var rightArr = new int[n2];

	for (var i = 0; i < n1; ++i) {
		leftArr[i] = arr[left + i];
	}

	for (var i = 0; i < n2; ++i) {
		rightArr[i] = arr[mid + 1 + i];
	}

	var i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (leftArr[i] <= rightArr[j]) {
			arr[k] = leftArr[i];
			++i;
		} else {
			arr[k] = rightArr[j];
			++j;
		}
		++k;
	}

	while (i < n1) {
		arr[k] = leftArr[i];
		++i;
		++k;
	}

	while (j < n2) {
		arr[k] = rightArr[j];
		++j;
		++k;
	}
}

