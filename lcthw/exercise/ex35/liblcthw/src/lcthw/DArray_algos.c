#include <lcthw/DArray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp) {
    Qsort(array->contents, 0, DArray_count(array)-1, sizeof(void *), cmp);
    return 0;
}

int Qsort(void **contents, size_t left, size_t right, size_t size, DArray_compare cmp){
     if ((left >= right)||((int)right <= 0)){
        return 0;
     }
     void *key = contents[left];
     printf("key: %s \n",(char *)key);
     int begin = left;
     int end = right;
     printf("begin:%d end:%d\n",begin,end);
     while (begin < end){
       	 printf("begin:%d end:%d\n",begin,end);
         while ((begin < end)&&(strcmp(contents[end], key))>=0){
             end--;	     
	 }
	 contents[begin] = contents[end];
	 
	 while ((begin < end)&&(strcmp(contents[begin], key)<=0)){
	     begin++;
	 }
	 contents[end] = contents[begin];
     }
     contents[begin] = key;
// Recursive sort
     Qsort(contents, left, begin-1, sizeof(void *), cmp);
     Qsort(contents, begin+1, right, sizeof(void *), cmp);
}



int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    heapsort(array->contents, 0, DArray_count(array)-1, sizeof(void *), cmp);
    return 0;
}

void heapsort(void **contents, size_t start, size_t end, size_t size, DArray_compare cmp){
    //构造大根堆(新插入的数上升)
    for (int i = 0; i < end + 1; i++) {
        int currentIndex = i;
        int fatherIndex = (currentIndex - 1) / 2;
        while (strcmp(contents[currentIndex], contents[fatherIndex]) > 0) {
            void *tmp = contents[currentIndex];
	    contents[currentIndex] = contents[fatherIndex];
	    contents[fatherIndex] = tmp;
            currentIndex = fatherIndex;
            fatherIndex = (currentIndex - 1) / 2;
        }
    }
    size_t length = end + 1;
    while (length > 1){
        void *tmp = contents[length - 1];
	contents[length - 1] = contents[0];
	contents[0] = tmp;
	//将剩下的继续构造大根堆(顶端的数下降)
	length--;
        heapify(contents, 0, length);
    }
}

void heapify(void **contents, size_t index, size_t length){
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    while (left < length) {
        int largestIndex;
        //判断孩子中较大的值的索引（要确保右孩子在length范围之内）
        if (strcmp(contents[left], contents[right]) < 0 && right < length) {
            largestIndex = right;
        } else {
            largestIndex = left;
        }
        //比较父结点的值与孩子中较大的值，并确定最大值的索引
        if (strcmp(contents[index], contents[largestIndex]) > 0) {
            largestIndex = index;
        }
        //如果父结点索引是最大值的索引，那已经是大根堆了，则退出循环
        if (index == largestIndex) {
            break;
        }
        //父结点不是最大值，与孩子中较大的值交换
        void *tmp = contents[largestIndex];
	contents[largestIndex] = contents[index];
	contents[index] = tmp;
        //将索引指向孩子中较大的值的索引
        index = largestIndex;
        //重新计算交换之后的孩子的索引
        left = 2 * index + 1;
        right = 2 * index + 2;
    }

}
                                                    
int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    void **tmp = calloc(DArray_count(array),sizeof(void *));
    mergesort(array->contents, 0, DArray_count(array)-1, sizeof(void *), cmp, tmp);
    if (tmp){
        free(tmp);
    }
    return 0;
}

void mergesort(void **contents, size_t left, size_t right, size_t size, DArray_compare cmp, void **tmp){
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergesort(contents,left,mid,size,cmp,tmp);
	mergesort(contents,mid+1,right,size,cmp,tmp);
        
        int i = left;
        int j = mid + 1;
        int index = 0;
        while (i <= mid && j <= right) {
            if (strcmp(contents[i], contents[j]) <= 0) {
                tmp[index] = contents[i];
		i++;
		index++;
            } else {
                tmp[index] = contents[j];
		j++;
		index++;
            }
        }
        // 剩余元素直接放入temp
        while (i <= mid) {
            tmp[index++] = contents[i++];
        }
        while (j <= right) {
            tmp[index++] = contents[j++];
        }
        // 放回原数组
        index = 0;
        while (left <= right) {
            contents[left++] = tmp[index++];
        }
    }    
}

