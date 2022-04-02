# DTree

This project is an implementation of a Descartes tree by an implicit key.

You can use any data type for the key.

    DTree<int> tree;
    
Have any methods:

    unsigned long long Size() - return size of tree.
    void Insert(KeyType value, unsigned long long poz) - insert value in poz pozition.
    void Erase(unsigned long long poz) - erase element in poz pozition.
    void Clear() - erase all tree with memory for it.
    
If you want set or get value from pozition, you can use operator []:
    
    DTree<long long> tree;
    tree.Insert(0, 0);
   
    std::cout << tree[0] << std::endl;
    tree[0] = 1;
    std::cout << tree[0] << std::endl;
    
Class safe, if you did some wrong, methods throw exceptions.
You can test class with command:
    
    make test
    make clean
    
You can watch stress and unit tests and add them if you want.

Class work garan work with compiler, version:

    g++ (GCC) 11.2.0
