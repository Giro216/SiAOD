#include "header.h"

int main()
{
    //setlocale(LC_ALL, "cp-866");
    //system("chcp 866");
    Enterprise **array_pointer = new Enterprise * [4000];
    read_bd(array_pointer);
    menu(array_pointer);

}

void menu(Enterprise** arr)
{
    int button = 0;
    while (button != 5)
    {
        switch (button)
        {
        case(0):
        {
            system("CLS");
            cout << "1\t" << "Write bd" << endl;
            cout << "2\t" << "Sort & write bd" << endl;
            cout << "3\t" << "Search" << endl;
            cout << "4\t" << "********" << endl;
            cout << "5\t" << "EXIT" << endl;

            cin >> button;
            break;
        }
        case(1):
        {
            print_bd(arr);
            button = 0;
            break;
        }
        case(2):
        {
            system("CLS");
            cout << "Sorting..." << endl;
            HeapSort_bd(arr);
            print_bd(arr);
            button = 0;
            break;
        }
        case(3):
        {
            system("CLS");
            
            int key;
            cout << "Enter date of birthday" << endl;
            cin >> key;

            int found = bin_search(arr, key);
            queue queue_of_found = create_queue(arr, found, key);
            print_queue(&queue_of_found);

            button = 0;
            break;
        }
        default:
            system("CLS");
            button = 0;
            cout << "ERROR: you whrote a wrong number" << endl;
            cout << "       Please try again" << endl;
            break;
        }
    }
}
   
void read_bd(Enterprise** arr)
{
    ifstream bd("obj/testBase2.dat", ios::binary);
    if (bd.is_open())
    {
        int count = 0;
        while (!bd.eof())
        {
            arr[count] = new Enterprise;
            bd.read((char*)arr[count], sizeof(*arr[count]));
            count++;
        }

        bd.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        exit(-1);
    }
}

void print_bd(Enterprise** arr)
{
    short int count = 0;
    int KB_code = 0;
    system("CLS");
    cout << "choose format of printing bd: by 20 items (<- or ->) or full bd (pgdn)" << endl;
    while (KB_code != KB_ESCAPE)
    {
        cout << "\nTo exit press Esc" << endl;
        KB_code = _getch();
        system("CLS");
        switch (KB_code)
        {
        case(KB_RIGHT):
        {
            if (count >= 3999) {
                cout << "it's a finish of bd." << endl;
                break;
            }
            for (int i = 0; i < 20; i++)
            {
                cout << count + 1 << "\t" << arr[count]->name << "\t" << arr[count]->job << "\t" << arr[count]->dep_number << "\t" << arr[count]->date << endl;
                count++;
            }
            break;
        }
        case(KB_LEFT):
        {
            count -= 40;
            if (count < 0)
            {
                //cout << "it's a start of bd. Please choose -> or pgdn" << endl;
                count = 4000;
                for (int i = 0; i < 20; i++)
                {
                    --count;
                    cout << count + 1 << "\t" << arr[count]->name << "\t" << arr[count]->job << "\t" << arr[count]->dep_number << "\t" << arr[count]->date << endl;
                }
                break;
            }
            for (int i = 0; i < 20; i++)
            {
                cout << count + 1 << "\t" << arr[count]->name << "\t" << arr[count]->job << "\t" << arr[count]->dep_number << "\t" << arr[count]->date << endl;
                count++;
            }
            break;
        }
        case(KB_DOWN):
        {
            for (int i = 0; i < 4000; i++)
            {
                cout << i + 1 << "\t" << arr[i]->name << "\t" << arr[i]->job << "\t" << arr[i]->dep_number << "\t" << arr[i]->date << endl;
            }
            break;
        }
        default:

            break;
        }
    }
    
}

void HeapSort_bd(Enterprise** array_pointer)
{
    int L = N / 2;
    while (L > 0)
    {
        Create_New_Heap(array_pointer, array_pointer[L - 1], L, N - 1);
        L--;
    }
    int R = N - 1;
    while (R > 0)
    {
        swap(array_pointer[0], array_pointer[R]);
        R--;
        Create_New_Heap(array_pointer, array_pointer[L], L + 1, R);
    }
}

void Create_New_Heap(Enterprise** array_pointer, Enterprise* key, int L, int R)
{
    bool flag = 1;
    int i = L - 1;
    while (flag == 1)
    {
        int j = (2 * i) + 1;
        if (j > R) {
            break;
        }
        if (j < R && (compression(array_pointer[j + 1], array_pointer[j]) == 1)){  //array_pointer[j + 1] > array_pointer[j]
            j++;
        }
        if (compression(key, array_pointer[j]) == 1) {
            break;
        }
        array_pointer[i] = array_pointer[j];
        i = j;
    }
    array_pointer[i] = key;
}

int Split_to_int(const char* str, char separator)
{
    int tokens[3];
    stringstream ss(str);
    string buff;
    int i = 0;

    while (getline(ss, buff, ' '))
    {
        int temp = stoi(buff);
        tokens[i] = temp;
        ++i;
    }

    return tokens[0];
}

int compression(Enterprise* left_p, Enterprise* right_p)
{
    int left_key = Split_to_int(left_p->date, '-');
    int right_key = Split_to_int(right_p->date, '-');

    if (left_key > right_key) {
        return 1;
    }
    else if (left_key < right_key) {
        return 0;
    }
    else
    {
        if (strcmp(left_p->name, right_p->name) > 0) {
            return 1;
        }
        else return 0;
    }
}

int bin_search(Enterprise** arr, int& key)
{
    for (int i = 0; i < 10; i++)
    {
        if (Split_to_int(arr[i]->date, ' ') > Split_to_int(arr[i + 1]->date, ' ')) {
            HeapSort_bd(arr);
            break;
        }
    }

    int mid;
    int L = 0;
    int R = N - 1;
    bool flag = false;
    while (L < R)
    {
        mid = Split_to_int(arr[(L + R) / 2]->date, ' ');

        if (mid < key) L = ((L + R) / 2) + 1;
        else {
            R = (L + R) / 2;
        }
    }
    if (Split_to_int(arr[L]->date, ' ') == key) {
        return L;
    }
    else {
        int temp;
        cout << "key didn't found" << endl;
        cout << "enter a new day of birth" << endl;
        cin >> temp;
        key = temp;
        system("CLS");
        return bin_search(arr, key);
    }
}

queue create_queue(Enterprise** arr, int index, int key)
{
    queue* queue_t = new queue;
    spis* current_spis = new spis(*arr[index]);
    queue_t->head = current_spis;

    ++index;
    while ((index < N) && (Split_to_int(arr[index]->date, '-') == key) )
    {
        spis* temp = new spis(*arr[index]);
        current_spis->next = temp;
        current_spis = temp;
        ++index;
    }
    queue_t->tail = current_spis;
    return *queue_t;
}

void print_queue(queue *head)
{
    int KB_code = 0;
    while (KB_code != KB_ESCAPE)
    {
        spis* temp = head->head;
        while (temp != NULL)
        {
            cout << temp->data.name << "\t" << temp->data.job << "\t" << temp->data.dep_number << "\t" << temp->data.date << endl;
            temp = temp->next;
        }

        cout << "\nTo exit press Esc" << endl;
        KB_code = _getch();
        system("CLS");
    }
}