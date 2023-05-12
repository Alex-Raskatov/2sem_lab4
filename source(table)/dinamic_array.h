#include <iostream>

struct DynamicArray {
  int * elements = nullptr;
  unsigned capacity = 0, size = 0;
};

DynamicArray new_array(unsigned size, int init_val = 0) {

    // создаёт в памяти новый массив, содержащий как минимум size элементов, каждый из которых равен значению init_val
    
    DynamicArray arr = DynamicArray{new int[size], size, size};
    
    for (int i = 0; i < size; i++) {
        arr.elements[i] = init_val;
    }
    return arr;
}

void erase(DynamicArray &da) {

    //удаляет массив, освобождает всю занятую им динамическую память, возвращает значения полей структуры к значениям по умолчанию

    delete [] da.elements;
    da.elements = nullptr;
    da.size = 0;
    da.capacity = 0;
}

bool in(DynamicArray &da, int key) {
    for (int i = 0; i < da.size; i++)
        if (da.elements[i] == key) return true;
    return false;
}

DynamicArray& reserve(DynamicArray &da, unsigned capacity) {

    /*гарантирует, что зарезервированная под массив память будет содержать как минимум capacity элементов,
    если текущая capacity больше запрашиваемой, то функция ничего не делает,
    если меньше – функция выделяет новую память содержащую не менее capacity элементов и копирует в неё все элементы,
    содержащие данные, старая память должна быть возвращена;
    функция возвращает ссылку на изменённую структуру DynamicArray; */

    if (capacity <= da.capacity) {
        return da;
    } else {
        int *elem = new int[capacity];
        for (int i = 0; i < da.size; i++) {
            elem[i] = da.elements[i];
        }
        delete [] da.elements;
        da.elements = elem;
        da.capacity = capacity;
        return da;
    }
}

DynamicArray clone(DynamicArray &da) {
    //возвращает новую структуру DynamicArray, которая содержит в новой памяти полную копию данных,
    //но количество зарезервированных элементов совпадает с количеством записанных;

    DynamicArray arr = DynamicArray{new int[da.size], da.size, da.size};
    
    for (int i = 0; i < da.size; i++) {
        arr.elements[i] = da.elements[i];
    }

    return arr;
}

DynamicArray& assign(DynamicArray const &src, DynamicArray &dst) {

    /*копирует записанные данные из массива src в массив dst, при этом данные массива dst полностью теряются,
    если в массиве dst недостаточно памяти, то функция увеличивает резерв памяти для dst.*/

    if (src.size > dst.capacity) {
        reserve(dst, src.size);
    }
    
    for (int i = 0; i < src.size; i++) {
        dst.elements[i] = src.elements[i];
    }
    dst.size = src.size;

    return dst;
}

DynamicArray& push_back_first(DynamicArray &da, int val) {
    /* добавляет в конец массив ещё один элемент со значением int_val. Если в массиве не до-
    статочно места, то функция расширяет количество занимаемой памяти. */
    if (da.capacity >= da.size + 1) {
        da.elements[da.size] = val;
        da.size++;
        return da;
    } else {
        reserve(da, da.size + 1).elements[da.size] = val;
        da.size++;
        return da;
    }
}

DynamicArray& push_back_second(DynamicArray &da, int val) {
    /* добавляет в конец массив ещё один элемент со значением int_val. Если в массиве не до-
    статочно места, то функция расширяет количество занимаемой памяти. */
    if (da.capacity >= da.size + 1) {
        da.elements[da.size] = val;
        da.size++;
        return da;
    } else {
        reserve(da, da.size + 1000).elements[da.size] = val;
        da.size++;
        return da;
    }
}

DynamicArray& push_back_third(DynamicArray &da, int val) {
    /* добавляет в конец массив ещё один элемент со значением int_val. Если в массиве не до-
    статочно места, то функция расширяет количество занимаемой памяти. */
    if (da.capacity >= da.size + 1) {
        da.elements[da.size] = val;
        da.size++;
        return da;
    } else {
        reserve(da, da.size*2);
        da.elements[da.size] = val;
        da.size++;
        return da;
    }
}