struct LinkedList {
    int data;
    LinkedList *next;
};

LinkedList* insert_after(LinkedList * const current, int key) {

    /* добавляет новый узел в существующий список сразу за переданным узлом
    с адресом current и возвращает указатель на созданный узел,
    если в качестве аргумента передано значение nullptr, то функция
    создаёт новый узел и возвращает его адрес */

    if (current == nullptr) return new LinkedList {key, nullptr};
    else {
        LinkedList *tmp = current->next;
        current->next = new LinkedList {key, tmp};
        return current->next;
    }
}

LinkedList* remove_after(LinkedList * const current) {

    /* удаляет из существующего списка узел, который идёт сразу за current,
    восстанавливает структуру списка и возвращает указатель на элемент,
    который теперь следует за элементом current, если в качестве аргумента
    передано значение nullptr, то функция ничего не делает и возвращает nullptr; */

    if (current == nullptr) return nullptr;
    else if (current->next == nullptr) return nullptr;
    else {
        LinkedList *tmp = current->next->next;
        delete current->next;
        current->next = tmp;
        return current->next;
    }
}

LinkedList* remove_value (LinkedList *head, int key) {
    if (head == nullptr) return nullptr;
    if (head != nullptr and head->data == key) {
        auto tmp = head->next;
        delete head;
        return tmp;
    }
    LinkedList* current = head;
    while (current->next != nullptr) {
        if (current->next->data == key) remove_after(current);
    }
    return head;
}

void erase(LinkedList * const head) {
    //считая, что узел по адресу head является началом списка, удаляет все узлы этого списка
    if (head == nullptr) return;
    else if (head->next == nullptr) {
        delete head;
        return;
    }
    else {
        erase(head->next);
        delete head;
        return;
    }
}

LinkedList* reverse_rec(LinkedList * const head) {
    // рекурсивно разварачивает список, элементы связываются в обратном порядке,
    // при этом сами элементы не меняют своего расположения в памяти и не копируются, изменяются только связи
    if (head == nullptr) return nullptr;
    else if (head->next == nullptr) return head;
    else {
        LinkedList *tmp = head->next;
        LinkedList *new_head = reverse_rec(head->next);
        tmp->next = head;
        head->next = nullptr;
        return new_head;
        //LinkedList *new_head = reverse_rec(head->next), *tmp = new_head;
        //while (tmp->next != nullptr) {
        //    tmp = tmp->next;
        //}
        //tmp->next = head;
        //head->next = nullptr;
        //return new_head;
    }
}

LinkedList* reverse_itr(LinkedList * const head) {
    // итерационно разварачивает список, элементы связываются в обратном порядке,
    // при этом сами элементы не меняют своего расположения в памяти и не копируются, изменяются только связи

    LinkedList *next_node = head->next, *current_node = head, *tmp;

    current_node->next = nullptr;

    while (next_node != nullptr) {
        tmp = current_node;             //сохраняем текущий элемент, который уже развернут
        current_node = next_node;       //сдвигаем текущий вперед
        next_node = next_node->next;    //сдвигаем следующий
        current_node->next = tmp;       //разворачиваем текущий
    }

    return current_node;
}