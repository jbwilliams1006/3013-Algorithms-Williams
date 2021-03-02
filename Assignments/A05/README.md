## Assignment 5 - Run Times
#### Due: 03-02-2021 (Tuesday @ 12:30 p.m.)


-----

- Count = __1024^2 = 1048576___________________
  
- Complexity = __O(n^2)______________
  
```cpp
int count = 0;
int n = 1024;
for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++){
        count++;
    }
}
cout<<count<<endl;
```

-----

- Count = __523776___________________
  
- Complexity = ___O(n^2)_____________
  
```cpp
int count = 0;
int n = 1024;
for(int i = 0; i < n; i++) {
    for(int j = 0; j < i; j++){
        count++;
    }
}
cout<<count<<endl;
```

-----

- Count = ____536346624_________________
  
- Complexity = __O(n^3)______________
  
```cpp
int count = 0;
int n = 1024;
for(int i = 0; i < n; i++) {
    for(int j = 0; j < i; j++){
        for(int k = 0; k < n; k++){
            count++;
        }
    }
}
cout<<count<<endl;
```

-----

- Count = ____2048_________________
  
- Complexity = ___O(n)_____________
  
```cpp
int count=0;
int n = 1024;
for(int i = 0; i < 2*n; i++) {
    count++;
}
cout<<count<<endl;
```

-----

- Count = ___2097152__________________
  
- Complexity = ________________
  
```cpp
int count=0;
int n = 1024;
for(int i = 0; i < n; i++) {
    for(int j = 0; j < 2n; j++){
        count++;
    }
}
cout<<count<<endl;
```

-----

- Count = ___524800__________________
  
- Complexity = ________________
  
```cpp
int count=0;
int n = 1024;
for(int i = 0; i < n; i++) {
    count++;
}
for(int j = 0; j < n; j++){
    for(int k = 0; k < j; k++){
        count++;
    }
}
cout<<count<<endl;
```

-----

- Count = _____11264________________
  
- Complexity = ________________
  
```cpp
int count = 0;
int n = 1024;
int i = n;

while(i>0){
    for(int j = 0; j < n; j++){
        count++;
    }
    i /= 2;
    cout<<i<<endl;
}
cout<<count<<endl;
```

-----

- Comparisons = __3_____________
  
- Complexity = __O(log n)______________
  
```cpp
bool found = 0;
int n = 1024;
int i = n;

// assume loaded with random numbers
// and in ascending order.
int *A = new int[n];

// Whats most number of comparisons?
// Whats the complexity?
found = BinarySearch(A,n);

```

-----

- Count = _____0________________
  
- Complexity = _____O(1)___________
  
```cpp
int count = 0;
int n = 1024;

int i = n;
while(i>0){
    cout<<i<<endl;
    i /= 2;  
}
cout<<count<<endl;
```

-----

### Deliverables

- banner page (you know what it is)
- print it
