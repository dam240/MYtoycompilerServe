struct list{
 void * value;
};

struct Arraylist{
 int size;
 int length;
 void *obj;
 int typesize;
 int list;
};


void * init(int size);
struct Arraylist * inif();
void add(struct Arraylist * list,void * obj);
void addALL(struct Arraylist * list,void * obj,int size,int len);
void * getarray(struct Arraylist * list,int index);
void * getObj(struct Arraylist * list);


