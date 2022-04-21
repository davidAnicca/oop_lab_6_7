#pragma once

template <typename ElementT>
class iteratorVector;

template <typename ElementT>
class Vector
{
public:
    /*
    Constructor default
    */
    Vector();

    /*
    Constructor de copiere
    */
    Vector(const Vector& ot); //rule of 3

    /*
    Eliberam memoria
    */
    ~Vector();//rule of 3

    /*
    Operator assgnment
    elibereaza ce era in obiectul curent (this)
    aloca spatiu pentru elemente
    copieaza elementele din ot in this
    */
    Vector& operator=(const Vector& ot);//rule of 3


    /*
    Move assignment
    Similar cu move constructor
    Folosit la assignment
    */
    Vector& operator=(Vector&& ot) noexcept ; //rule of 5


    void add(const ElementT& el);

    ElementT& get(int poz) const;

    void set(int poz, const ElementT& el);
    void erase(int poz);
    int size() const noexcept;

    friend class iteratorVector<ElementT>;
    //functii care creaza iteratori
    iteratorVector<ElementT> begin() const;
    iteratorVector<ElementT> end() const;


private:
    int lg;//numar elemente
    int cap;//capacitate
    ElementT* elems;//elemente

    void ensureCapacity();
};



/*
Constructor default
*/
template<typename ElementT>
Vector<ElementT>::Vector() :elems{new ElementT[100] }, cap{100 }, lg{0}{}

/*
Constructor de copiere
Obiectul current (this) acum se creaza
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
template<typename ElementT>
Vector<ElementT>::Vector(const Vector<ElementT>& ot) {
    elems = new ElementT[ot.cap];
    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];
    }
    lg = ot.lg;
    cap = ot.cap;
}

/*
Operator assgnment
*/
template<typename ElementT>
Vector<ElementT>& Vector<ElementT>::operator=(const Vector<ElementT>& ot) {
    if (this == &ot) {
        return *this;//s-a facut l=l;
    }
    delete[] elems;
    elems = new ElementT[ot.cap];
    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];  //assignment din Pet
    }
    lg = ot.lg;
    cap = ot.cap;
    return *this;
}

/*
Eliberam memoria
*/
template<typename ElementT>
Vector<ElementT>::~Vector() {
    delete[] elems;
}
/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obiectul curent (this)
"fura" interiorul lui ot
pregateste ot pentru distrugere
*/
template<typename ElementT>
Vector<ElementT>& Vector<ElementT>::operator=(Vector<ElementT>&& ot)  noexcept {
    if (this == &ot) {
        return *this;
    }
    delete[] elems;
    elems = ot.elems;
    lg = ot.lg;
    cap = ot.cap;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    ot.elems = nullptr;
    ot.lg = 0;
    ot.cap = 0;
    return *this;
}

template<typename ElementT>
void Vector<ElementT>::add(const ElementT& el) {
    ensureCapacity();//daca e nevoie mai alocam memorie
    elems[lg++] = el;
}

template<typename ElementT>
ElementT& Vector<ElementT>::get(int poz) const {
    return elems[poz];
}

template<typename ElementT>
void Vector<ElementT>::set(int poz, const ElementT& el) {
    elems[poz] = el;
}

template<typename ElementT>
int Vector<ElementT>::size() const noexcept {
    return lg;
}

template<typename ElementT>
void Vector<ElementT>::ensureCapacity() {
    if (lg < cap) {
        return; //mai avem loc
    }
    cap *= 2;
    auto* aux = new ElementT[cap];
    for (int i = 0; i < lg; i++) {
        aux[i] = elems[i];
    }
    delete[] elems;
    elems = aux;
}

template<typename ElementT>
iteratorVector<ElementT> Vector<ElementT>::begin() const {
    return iteratorVector<ElementT>(*this);
}

template<typename ElementT>
iteratorVector<ElementT> Vector<ElementT>::end() const {
    return iteratorVector<ElementT>(*this, lg);
}

template<typename ElementT>
class iteratorVector {
private:
    const Vector<ElementT>& v;
    int poz = 0;
public:
    explicit iteratorVector(const Vector<ElementT>& v) noexcept;
    iteratorVector(const Vector<ElementT>& v, int poz)noexcept;
    bool valid()const;
    ElementT& element() const;
    void next();
    ElementT& operator*();
    iteratorVector& operator++();
    bool operator==(const iteratorVector& ot)noexcept;
    bool operator!=(const iteratorVector& ot)noexcept;
};

template<typename ElementT>
void Vector<ElementT>::erase(int poz) {
    if(poz < 0 || poz > lg){
        ///error #TODO
    }
    ElementT& elementT = get(poz);
    for(int i = poz; i < lg-1; i++){
        elems[i] = elems[i+1];
    }
    lg--;
}

template<typename ElementT>
iteratorVector<ElementT>::iteratorVector(const Vector<ElementT>& v) noexcept:v{v}{}

template<typename ElementT>
iteratorVector<ElementT>::iteratorVector(const Vector<ElementT>& v, int poz)noexcept : v{v }, poz{poz} {}

template<typename ElementT>
bool iteratorVector<ElementT>::valid()const {
    return poz < v.lg;
}

template<typename ElementT>
ElementT& iteratorVector<ElementT>::element() const {
    return v.elems[poz];
}

template<typename ElementT>
void iteratorVector<ElementT>::next() {
    poz++;
}

template<typename ElementT>
ElementT& iteratorVector<ElementT>::operator*() {
    return element();
}

template<typename ElementT>
iteratorVector<ElementT>& iteratorVector<ElementT>::operator++() {
    next();
    return *this;
}

template<typename ElementT>
bool iteratorVector<ElementT>::operator==(const iteratorVector<ElementT>& ot) noexcept {
    return poz == ot.poz;
}

template<typename ElementT>
bool iteratorVector<ElementT>::operator!=(const iteratorVector<ElementT>& ot)noexcept {
    return !(*this == ot);
}



