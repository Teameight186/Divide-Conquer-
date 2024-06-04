template<class T> class List{
private:
    ListNode<T> *header;
    ListNode<T> *win;
    int _length;
    public:
    List();
    ~List();
    T insert(T);
    T append(T);
    List *append(List*);
    T prepend(T);
    T remove();
    void val(T);
    T val();
    T next();
    T prev();
    T first();
    T last();
    int length();
    bool isFirst();
    bool isLast();
    bool isHead();
};

template<class T> List<T>::List():_length(0)
{
    header = new ListNode<T>(NULL);
    win = header;
}