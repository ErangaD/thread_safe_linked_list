#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

struct list_node_s {
    int data;
    struct list_node_s* next;
};

int number_of_member_op;
int number_of_insert_op;
int number_of_delete_op;

int Member(int value, struct list_node_s* head_p);
int Delete(int value, struct list_node_s** head_pp);
int Insert(int value, struct list_node_s** head_pp);
void* do_operations();
struct list_node_s* head_p;

int main(int args, char* argv[]){

    int n =  strtol(argv[1], NULL ,10);
    int m =  strtol(argv[2], NULL ,10);
    double M_member = atof(argv[3]);
    double M_insert = atof(argv[4]);

    number_of_member_op = (int)(M_member * m);
    number_of_insert_op = (int)(M_insert * m);
    number_of_delete_op = m - (number_of_member_op + number_of_insert_op);

    head_p = malloc(sizeof(struct list_node_s));;
    int header_data = rand() % USHRT_MAX;
    head_p->data = header_data;

    int i=0;
    while (i < n-1) {

        int local_data_value = rand() % USHRT_MAX;
        int is_success = Insert(local_data_value, &head_p);
	//checking whether insert is success --> to identify dupliicate values
        if (is_success == 0)
            continue;
        i++;

    }

    clock_t begin = clock();

    do_operations();

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time to execute = %fs\n", time_spent);


}

void* do_operations(){

    int random_number;

    while(1) {

        if (number_of_delete_op == 0 && number_of_insert_op == 0 && number_of_member_op == 0) {
	    //check whehter there are operations to execute 
            break;
        }

        if (number_of_member_op != 0) {
            random_number = rand() % USHRT_MAX;
            Member(random_number, head_p);
            number_of_member_op--;
        }
        if (number_of_insert_op != 0) {
            random_number = rand() % USHRT_MAX;
            Insert(random_number, &head_p);
            number_of_insert_op--;
        }
        if (number_of_delete_op != 0) {
            random_number = rand() % USHRT_MAX;
            Delete(random_number, &head_p);
            number_of_delete_op--;
        }

    }

    return NULL;
}


int Member(int value, struct list_node_s* head_p) {
    struct list_node_s* curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;
    if (curr_p == NULL || curr_p->data < value) {
        return 0;
    } else {
        return 1;
    }

}



int Insert(int value, struct list_node_s** head_pp){
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL) {
            *head_pp = temp_p;
        }else {
            pred_p->next = temp_p;
        }
        return 1;
    } else {
        return 0;
    }

}

int Delete(int value, struct list_node_s** head_pp) {
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) {
            *head_pp = curr_p->next;
        } else {
            pred_p->next = curr_p->next;
        }
        free(curr_p);
        return 1;
    } else {
        return 0;
    }
}

