#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <unordered_map>

using namespace std;
//1 2 3 4 5 7
int find_first_missing_number_helper(int *arr, int start, int end)
{
   //base cases
   int mid = (start + end) / 2;
   int offset = mid - start;

   if (start >= end) return 0;
   if ((arr[mid] + 1) != arr[mid+1]) return (arr[mid] + 1);

   if ((arr[start]+ offset) < arr[mid]) {
       return find_first_missing_number_helper(arr, start, (mid));
   } else {
       return find_first_missing_number_helper(arr, mid+1, end);
   }
}

int find_first_missing_number(int *arr, int size)
{
    if ((size == 0) || (size == 1)) { return 0;}
    
    return find_first_missing_number_helper(arr, 0, size-1);
}

int find_first_duplicate_number(int *arr, int start, int end)
{
    //base case
    int mid = (start+end)/2;
    int offset = mid - start;
    if (start >= end) {return -1;} //no duplication
    if (arr[mid] == arr[mid+1]) {return arr[mid];}

    //recursion
    if ((arr[start]+offset) < arr[mid]) {
        return find_first_duplicate_number(arr, start, mid);
    } else {
        return find_first_duplicate_number(arr, mid+1, end);
    }
}

// 1 2 3 3 3 3 4
// 1 3 
int find_first_target_number_in_sorted_array(int *arr, int start, int end, int target)
{
    //base cases
    int mid = (start + end) / 2; 
    if (start == end) {
        if (arr[start] == target) {
            return start;
        } else {
            return -1;
        }
    }
    
    
    if ((arr[mid] != arr[mid+1]) && (arr[mid+1] == target)) {
        return mid+1;
    }

    if (arr[mid] >= target) {
        return find_first_target_number_in_sorted_array(arr, start, mid, target);
    } else {
        return find_first_target_number_in_sorted_array(arr, (mid+1), end, target);    
    }
}

// 1 3 3 3 3 5 6
// 1 3
// 1 1 3 3 
int find_last_target_number_in_sorted_array(int *arr, int start, int end, int target)
{
    //base cases
    if (start == end) {
        if (arr[start] == target) {
            return start;
        } else {
            printf("last index for target %d is not found\n", target);
            return -1;
        }
    }

    int mid = (start + end) / 2;

    
    if ((arr[mid] == target) && (arr[mid+1] != target)) {
        return mid; //this is the last occurance of the target
    } else {
        if (arr[mid] > target) {
            return find_last_target_number_in_sorted_array(arr, start, mid, target);
        } else {
            return find_last_target_number_in_sorted_array(arr, mid+1, end, target);
        }
    } 
}

int find_target_number_occurance(int *arr, int start, int end, int target)
{
    int first = find_first_target_number_in_sorted_array(arr, start, end, target);
    if (first == -1) {
        printf("target number %d is not found\n", target);
        return -1;
    }

    int last = find_last_target_number_in_sorted_array(arr, start, end, target);
    if (last == -1) {
        printf("invalid last index\n");
        return -1;
    }
    printf(" target %d occurs %d times\n", target, (last-first+1));
    return (last - first + 1);
}

int climb_stairs_helper(int steps, int *buffer)
{
    if (steps == 1) return 1;
    if (steps == 2) return 2;

    if (buffer[steps] > 0) return buffer[steps]; //return value from the cache

    buffer[steps] = climb_stairs_helper((steps-1), buffer) + climb_stairs_helper((steps-2), buffer);
    return buffer[steps];
}

int climb_stairs(int steps)
{
    int buffer[steps+1] = {0};
    int result = 0;
    result = climb_stairs_helper(steps, buffer);
    printf(" result for %d steps is %d\n", steps, result);
    return result;
}

int find_element_in_rotated_array(int *arr, int start, int end, int target)
{
    // base cases
    if (start == end) {
        if (arr[start] != target) {
            return (-1); //no element is found within the array
        } else {
            return start;
        }
    }

    int mid = (start + end) / 2;
    if (arr[mid] == target) return mid;

    if (arr[mid] == arr[start]) {
        if (arr[mid] == arr[end]) {
            //Need to search both left and right
            int index = find_element_in_rotated_array(arr, start, (mid-1), target);
            if (index >= 0) return index;
            return find_element_in_rotated_array(arr, (mid+1), end, target);
         } else {
            return find_element_in_rotated_array(arr, (mid+1), end, target);
         }
    } else if (arr[mid] < arr[end]){    
            if ((arr[mid] < target) && (target <= arr[end])) {
                //target is on the right porition of the array (sorted)
                return find_element_in_rotated_array(arr, (mid+1), end, target);
            } else {
                return find_element_in_rotated_array(arr, start, (mid-1), target);
            }
    } else if (arr[mid] > arr[start]) {
            if ((arr[mid] > target) && (target >= arr[start])) {
                //left side is sorted
                return find_element_in_rotated_array(arr, start, (mid-1), target);
            } else {
                return find_element_in_rotated_array(arr, (mid+1), end, target);
            }
    }
    return (-1);    
}

int find_number_in_rotated_array(int *arr, int size, int target)
{
    int pos = find_element_in_rotated_array(arr, 0, (size-1), target);
    printf(" target %d is in position %d\n", target, pos);
    return pos;
}

int count_rotations_helper(int *arr, int start, int end)
{
    //base cases
    if (start == end) return 0; //no rotation in the array
    int mid = (start + end) / 2;

    if (arr[mid] > arr[mid+1]) {
        return (mid+1); //mid+1 contains the smallest number in the array
    }

    if (arr[mid] == arr[start]) {
        if(arr[mid] < arr[end]) {
             //the right side is sorted
             return count_rotations_helper(arr, start, mid);
        } else if (arr[mid] > arr[end]) {
             return count_rotations_helper(arr, (mid+1), end);
        } else {
             // need to search both sides
             int temp = count_rotations_helper(arr, start, mid);
             if (temp > 0) return temp;
             return count_rotations_helper(arr, (mid+1), end);
        }
    } else if (arr[mid] > arr[start]) {
        return count_rotations_helper(arr, (mid+1), end);
    } else {
        return count_rotations_helper(arr, start, mid);
    }
}

int count_rotations_in_sorted_array(int *arr, int size)
{
    int rotate_num = count_rotations_helper(arr, 0, (size-1));
    printf(" rotation is : %d\n", rotate_num); 
}

void print_subset_helper(vector< int > &subset)
{
    for (int i : subset) {
        printf(" %d ", i);
    }
    printf("\n");
}

void print_subsets_in_array(int *array, int size, vector<vector< int > > &subsets)
{  
    if (size == 0) return; //return an empty subset
    
    print_subsets_in_array(array, (size - 1), subsets);   
    
    int element = array[size-1]; //get the number at size-1
        
    for (int i=0; i<subsets.size(); i++) {
        subsets[i].push_back(element);
        print_subset_helper(subsets[i]);
    }

    vector< int > temp;
    temp.push_back(element);
    subsets.push_back(move(temp));
    printf(" %d\n", element);
}

void print_powerset(int *arr, int size)
{
    vector<vector< int > > subsets;
    print_subsets_in_array(arr, size, subsets);
}

void print_target_sum_pairs(int *arr, int size, int target_sum)
{
    unordered_map<int, int> complement;
    
    for (int i=0; i<size; i++) {
        int difference = target_sum - arr[i];
        if (complement[difference] == 0) { //no complement pair is found
            complement[arr[i]]++; //increment the complement count
        } else if (complement[difference] > 0) {
            printf(" Pair: %d + %d = %d\n", arr[i], difference, target_sum);
            complement[difference]--;
        }
     }  
}

void merge(int *arr, int *helper, int start, int mid, int end)
{
    int left1 = start;
    int left2 = mid;
    int right1 = mid+1;
    int right2 = end;
    int current = left1;

    while ((left1 <= left2) && (right1 <= right2)) {
        if (arr[left1] <= arr[right1]) {
            helper[current] = arr[left1];
            left1++;
        } else {
            helper[current] = arr[right1];
            right1++;
        }
        current++;
    }

    //copy the remaining elements
    while (left1 <= left2) {
        helper[current++] = arr[left1];
        left1++;
    }

    while (right1 <= right2) {
        helper[current++] = arr[right1];
        right1++;
    }

    //copy the sorted items back to the original array;
    for (int i=start; i<=end; i++) {
        arr[i] = helper[i];
    }
}

void merge_sort_helper(int *arr, int *helper, int start, int end)
{
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort_helper(arr, helper, start, mid);
        merge_sort_helper(arr, helper, (mid+1), end);
        merge(arr, helper, start, mid, end);
    }
}

void merge_sort(int *arr, int size)
{
   int helper[size] = {0};
   merge_sort_helper(arr, helper, 0, (size-1));
   
   printf("Array after sorting: \n");
   for (int i=0; i<size; i++) {
       printf(" %d", arr[i]);
   }
   printf("\n");
}

void test_merge_sort()
{
    int arr1[2] = {2, 1};
    int arr2[3] = {3, 1, 2};
    int arr3[4] = {1, 2, 4, 3};
    int arr4[4] = {2, 1, 3, 4};
    int arr5[5] = {5, 2, 1, 3, 4};
    int arr6[5] = {5, 2, 1, 4, 3};
    int arr7[5] = {5, 4, 3, 2, 1};

    merge_sort(arr1, 2);
    merge_sort(arr2, 3);
    merge_sort(arr3, 4);
    merge_sort(arr4, 4);
    merge_sort(arr5, 5);
    merge_sort(arr6, 5);  
    merge_sort(arr7, 5);     
}
void test_print_subset()
{
    int arr1[1] = {1};
    int arr2[2] = {1, 2};
    int arr3[3] = {1, 2, 3};
    int arr4[4] = {1, 2, 2, 3};

    print_powerset(arr1, 1);
    printf("\n");
    print_powerset(arr2, 2);
    printf("\n");
    print_powerset(arr3, 3);
    printf("\n");
    print_powerset(arr4, 4);
    printf("\n");
}

void test_print_target_sum_pairs()
{
    int arr_1[1] = {1};
    int arr_2[2] = {1,2};
    int arr_3[3] = {1,3,5};
    int arr_4[4] = {1,2,0,4};
    int arr_5[5] = {1,2,0,4,1};
    int arr_6[8] = {7,1,6,2,5,3,2,6};
    int arr_7[7] = {7,2,2,7,3,6,9};
    
    print_target_sum_pairs(arr_2, 1, 2);
    print_target_sum_pairs(arr_2, 2, 3);
    print_target_sum_pairs(arr_3, 3, 6);
    print_target_sum_pairs(arr_4, 4, 4);
    print_target_sum_pairs(arr_5, 5, 5);
    print_target_sum_pairs(arr_6, 8, 8);
    print_target_sum_pairs(arr_7, 8, 9);
}

void test_count_rotations_in_sorted_array()
{
    int arr1[2] = {3, 1};
    int arr2[3] = {3, 1, 2};
    int arr3[3] = {2, 3, 1};
    int arr4[4] = {3, 4, 1, 2};
    int arr5[4] = {2, 3, 4, 1};
    int arr6[5] = {3, 3, 3, 2, 3};
    int arr7[5] = {3, 2, 3, 3, 3};
    int arr8[5] = {3, 3, 3, 3, 3};

    count_rotations_in_sorted_array(arr1, 2);
    count_rotations_in_sorted_array(arr2, 3);
    count_rotations_in_sorted_array(arr3, 3);
    count_rotations_in_sorted_array(arr4, 4);
    count_rotations_in_sorted_array(arr5, 4);
    count_rotations_in_sorted_array(arr6, 5);
    count_rotations_in_sorted_array(arr7, 5);
    count_rotations_in_sorted_array(arr8, 5);
}

void test_find_number_in_rotated_array()
{
    int arr1[2] = {3, 1};
    int arr2[3] = {3, 1, 2};
    int arr3[3] = {2, 3, 1};
    int arr4[4] = {3, 4, 1, 2};
    int arr5[4] = {2, 3, 4, 1};
    int arr6[5] = {3, 3, 1, 2, 2};
    int arr7[5] = {3, 3, 1, 2, 3};

    find_number_in_rotated_array(arr1, 2, 3);
    find_number_in_rotated_array(arr1, 2, 1);
    find_number_in_rotated_array(arr2, 3, 2);
    find_number_in_rotated_array(arr3, 3, 2);
    find_number_in_rotated_array(arr4, 4, 4);
    find_number_in_rotated_array(arr5, 4, 1);
    find_number_in_rotated_array(arr6, 5, 3);
    find_number_in_rotated_array(arr7, 5, 2);    
}

void test_climb_stairs()
{
    climb_stairs(1);
    climb_stairs(2);
    climb_stairs(3);
    climb_stairs(4);
    climb_stairs(5);
    climb_stairs(6);
    climb_stairs(7);
}

void test_find_target_number_occurance()
{
    // test cases:
    int arr1[1] = {1};
    int arr2[2] = {1, 3};
    int arr3[3] = {1, 3, 3};
    int arr4[4] = {1, 3, 3, 3};
    int arr5[5] = {1, 2, 2, 2, 3};
    int arr6[6] = {2, 2, 2, 2, 2, 2};
    

    printf("%s\n", __func__);
    
    int rc_1 = find_target_number_occurance(arr1, 0, 0, 1);
    int rc_2 = find_target_number_occurance(arr2, 0, 1, 1);
    int rc_3 = find_target_number_occurance(arr3, 0, 2, 1);
    int rc_4 = find_target_number_occurance(arr4, 0, 3, 3);
    int rc_5 = find_target_number_occurance(arr5, 0, 4, 2);
    int rc_6 = find_target_number_occurance(arr6, 0, 5, 2);
    int rc_7 = find_target_number_occurance(arr6, 0, 5, 1);
}

void test_first_missing_number()
{
    int a1[1] = {1};
    int a2[2] = {2, 4};
    int a3[3] = {2, 3, 4};
    int a4[4] = {2, 3, 5, 6};
    int a5[4] = {2, 4, 5, 6};
    int a6[5] = {1, 2, 3, 5, 6};
    int a7[5] = {1, 2, 3, 4, 6};

    printf("%s\n", __func__);

    int rc_1 = find_first_missing_number(a1, 1);
    int rc_2 = find_first_missing_number(a2, 2);
    int rc_3 = find_first_missing_number(a3, 3);
    int rc_4 = find_first_missing_number(a4, 4);
    int rc_5 = find_first_missing_number(a5, 4);
    int rc_6 = find_first_missing_number(a6, 6);
    int rc_7 = find_first_missing_number(a7, 7);

    printf("Results: %d %d %d %d %d %d %d\n", rc_1, rc_2, rc_3, rc_4, rc_5, rc_6, rc_7);
}

int main()
{
    //test_first_missing_number();
    //test_find_target_number_occurance();
    //test_climb_stairs();
    //test_find_number_in_rotated_array();
    //test_count_rotations_in_sorted_array();
    //test_print_target_sum_pairs();
    //test_print_subset();
    test_merge_sort();
}
