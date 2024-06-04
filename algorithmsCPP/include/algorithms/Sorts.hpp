template<class T>
void mergeSort(T a[], int n, int (*cmp)(T,T))
{
  mSort(a, 0, n-i, cmp);  
}

template<class T>
void mSort(T a[], int l, int r, int (*cmp)(T,T)){
  if (1 < r) {
    int m = (l + r) / 2;
    mSort(a, l, m, cmp);
    mSort(a, m+l, r, cmp);
    merge(a, l, m, r, cmp);
  } 
}

template<class T>
void merge(T x[], int l, int m, int r, int (*cmp) (T,T))
{
  T *a = x+l;
  T *b = x+m+l;
  T *c = new T[r-l+1];
  int aindx = 0, bindx = 0, cindx = 0;
  int alim = m-l+1, blim = r-m;
  while ((aindx < alim) && (bindx < blim)){
    if ((*cmp)(a[aindx], b[bindx]) < 0){
      c[cindx++] = a[aindx++];
    }
    else{
      c[cindx++] = b[bindx++];
    }

  }
  while (aindx < alim){
    c[cindx++] = a[aindx++];
  }
  while (bindx < blim){
    c[cindx++] = b[bindx++];
  }

  for (aindx=cindx=O; aindx <= r-1; a[aindx++] = c[cindx++]);
  delete c;
}




// #include <iostream>
// #include <vector>
// #include <iterator>

// namespace merge {
//   template<typename it, typename comp>
//   std::vector<typename std::iterator_traits<it>::value_type> merge(const it begin, const it& mid, const it& end, comp compare)
//   {
//     std::vector<typename std::iterator_traits<it>::value_type> buffer;
//     buffer.reserve(std::distance(begin, end));
//     it it_l{ begin }, it_r{ mid };

//     while (it_l != mid && it_r != end)
//     {
//       buffer.push_back(std::move(compare(*it_l, *it_r) ? *it_l++ : *it_r++));
//     }

//     buffer.insert(buffer.end(), it_l, mid);
//     buffer.insert(buffer.end(), it_r, end);

//     return buffer;
//   }
// }

// template<typename it, typename comp = std::less<typename std::iterator_traits<it>::value_type>>
// void mergeSort(it begin, it end, comp compare = comp())
// {
//   auto size = std::distance(begin, end);
//   if (size < 2)
//     return;

//   auto mid = std::next(begin, size / 2);
//   mergeSort(begin, mid);
//   mergeSort(mid, end);

//   auto v = merge::merge(begin, mid, end, compare);
//   std::move(v.begin(), v.end(), begin);
// }

// template<typename it>
// void print(it begin, it end) {
//   while (begin != end) {
//     std::cout << *(begin++) << " ";
//   }
//   std::cout << '\n';
// }