#include <stdio.h>
#include <stdlib.h>

#define TIME_QUANTUM 10;

/* STRUCTURES NEEDED */

typedef struct _pro {
	int p_no, count;
	int arr_t, wait_t, burst_t;
	int start_t, fin_t;
}_pro;

typedef struct _elem {
	int no;
	_pro* proc;
	struct _elem* next;
	struct _elem* front;
}_elem;

typedef struct _queue {
	_elem* head;
	_elem* rear;
	int count;
	int size;
}_q;



/* create structures functions */
_elem* createElement(_pro* proc)
{
	_elem* myelem = (_elem*)malloc(sizeof(_elem));
	myelem->front = NULL;
	myelem->next = NULL;
	myelem->no = proc->p_no;
	myelem->proc = proc;
	return myelem;
}
_q* createQueue(int s) {
	_q* q = (_q*)malloc(sizeof(_q));
	q->head = NULL;
	q->rear = NULL;
	q->count = 0;
	q->size = s;
	printf("Queue created! size: %d \n", q->size);
	return q;
}


/* functions for queuing */

int isEmpty(_q* myqueue) {
	if (myqueue->count == 0) {
		//printf("is empty \n");
		return 1;
	}
	else {
		//printf("isn't empty \n");
		return 0;
	}
}


int isFull(_q* myqueue) {
	if (myqueue->count == myqueue->size) {
		//printf("is full \n");
		return 1;
	}
	else {
		//printf("isn't full \n");
		return 0;
	}
}

/* enqueue */
/* put in according to arrival time */
_q* q_enqueue(_q* q, _pro* proc)
{
	//check if it's full
	if (isFull(q)) {
		printf("the queue is full \n");
		return NULL;
	}
	// allocate memory for queue element
	_elem* myelem = createElement(proc);

	//the queue is empty
	if (isEmpty(q)) {
		q->head = myelem;
		q->rear = myelem;
		q->count++;
		//q_print_p(q);
		return q;
	}
	//traverse through the queue to find the right place
	_elem* ptr = q->head;
	//printf("current ptr: %d \n", ptr->no);
	while (ptr != NULL) {
		if (myelem->proc->arr_t < ptr->proc->arr_t) {
			if (ptr == q->head) {
				ptr->front = myelem;
				myelem->next = ptr;
				q->head = myelem;
				//printf("put in head \n");
				q->count++;
				//q_print_p(q);
				return q;
			}
			// 헤드 아닌 거 앞
			myelem->next = ptr;
			myelem->front = ptr->front;
			myelem->front->next = myelem;
			ptr->front = myelem;
			q->count++;
			//q_print_p(q);
			return q;
		}
		else {
			ptr = ptr->next;
			//printf("ptr moved to %d \n", ptr->no);
		}
	}
	// traverse 다 했는데, 못찾은거 -> 끝에 들어가야함
	q->rear->next = myelem;
	myelem->front = q->rear;
	q->rear = myelem;
	q->count++;
	//printf("put in tail \n");
	//q_print_p(q);
	return q;
}
/*
p_continue
	is when the process is not done and the time quantum is gone
		1) get the element as a paramter
		2) put the element to the rear of the queue
*/
_q* q_continue(_q* q, _elem* myelem) {
	if (isFull(q))
	{
		printf("The queue is full! \n:");
		return q;
	}
	// put in the element
	q->rear->next = myelem;
	myelem->front = q->rear;
	q->rear = myelem;
	q->count++;
	//printf("enqueued again %d / queue size: %d \n", myelem->no, q->count);
	return q;
}


/* retrieve
	get the process from the queue to execute the process
*/
_elem* q_retrieve(_q* q)
{
	if (isEmpty(q)) {
		printf("The queue is empty! \n");
		return 0;
	}
	_elem* temp = q->head;
	q->head = q->head->next;
	q->count--;
	//printf("%d \n", q->count);
	return temp;
}

/* elem_free
	The process is done and no need to be queued again. Free the memory.
*/
int elem_free(_q* q) {
	if (isEmpty(q)) {
		printf("Error! \n");
		return -1;
	}
	q->head = q->head->next;
	q->head->next->front = NULL;
	_elem* temp = q->head;
	q->head = q->head->next;
	free(temp);
	q->count--;
	return 0;
}

/* PRINT QUEUE STATUS */
int q_print_p(_q* myqueue) {
	_elem* temp = myqueue->head;
	printf("\n ----------------------------------- QUEUE STATUS ------------------------------- \n \n");
	for (int i = 0; i < myqueue->count; i++) {
		printf("[ entry %d ] : count: %d   arr: %d   wait: %d   burst: %d   start: %d   fin: %d \n",
			temp->proc->p_no, temp->proc->count, temp->proc->arr_t, temp->proc->wait_t,
			temp->proc->burst_t, temp->proc->start_t, temp->proc->fin_t);
		temp = temp->next;
	}
	printf(" ---------------------------------------- ------------------------------------------\n \n");
	return 0;
}

///////////////////////// PROCESS FUNCTIONS -/////////////////////////

/* create processes */
_pro* createP(int p_no) {
	srand(p_no * 348);
	_pro* proc = malloc(sizeof(_pro));
	proc->p_no = p_no;
	proc->count = 0;
	proc->burst_t = ((rand() % 10) * 3) + 10;
	proc->arr_t = rand() % 50;
	proc->fin_t = 0;
	proc->start_t = 0;
	proc->wait_t = 0;
	printf("process %d created!  \n", proc->p_no);
	return proc;
}

int pprint(_pro* proc) {
	printf("[ entry %d ] : count: %d   arr: %d   wait: %d   burst: %d   start: %d   fin: %d \n",
		proc->p_no, proc->count, proc->arr_t, proc->wait_t,
		proc->burst_t, proc->start_t, proc->fin_t);
	return 0;
}


/* burst process
	parameters: curt - the time started execution
	returns finished process time
*/
int simple_exe(_pro* proc, int* curt) {
	proc->start_t = *curt;
	proc->wait_t = *curt - proc->arr_t;
	if (proc->wait_t < 0) {
		proc->wait_t = 0;
	}
	*curt = *curt + proc->burst_t;
	proc->fin_t = *curt;
	return 0;
}

/* burst process for round robin */

int rr_exe(_q* myqueue, _elem* myelem, int* curt) {
	//printf("start execution %d \n", myelem->proc->p_no);
	if (myelem->proc->count == 0) {
		// 처음으로 실행됨
		myelem->proc->start_t = *curt;
		if (*curt - myelem->proc->arr_t < 0) {
			myelem->proc->wait_t = 0;
		}
		else {
			myelem->proc->wait_t = *curt - myelem->proc->arr_t;
		}
	}
	// 처음 아님
	else {
		myelem->proc->wait_t += *curt - myelem->proc->fin_t;
	}
	int temp = myelem->proc->burst_t - TIME_QUANTUM;
	if (temp<=0){
		// burst 끝남
		myelem->proc->fin_t = *curt + myelem->proc->burst_t;
		myelem->proc->burst_t = 0;
		*curt = myelem->proc->fin_t;
		return 0;
	}
	// 아직 다 끝나지 않았음.
	myelem->proc->burst_t -= TIME_QUANTUM;
	myelem->proc->count++;
	myelem->proc->fin_t = *curt + TIME_QUANTUM;
	*curt = *curt + TIME_QUANTUM;
	q_continue(myqueue, myelem);
	return 0;
}

/* get array of processes and computes the average of waiting time */
int get_avr(_pro* arr[], int arr_size) {
	int sum = 0;
	int avr = 0;
	for (int i = 0; i < arr_size; i++) {
		sum = sum + arr[i]->wait_t;
	}
	avr = sum / arr_size;
	return avr;
}


/* dequeue for sjf: used to compare arr_t and burst_t */
_elem* sjf_dequeue(_q* q, int compare_t) {
	//q_print_p(q);

	if (q->count == 0) {
		printf("The queue is empty! \n");
		return 0;
	}
	_elem* ptr = q->head; // used for traversing
	_elem* shortest = NULL; // used to save shortest job among arrived tasks
	//printf("%d \n", compare_t);
	while (ptr != NULL && ptr->proc->arr_t < compare_t) {
		// burst 중 도착한 것
		if (shortest == NULL) { // 처음입니다
			shortest = ptr; // burst_t 짧은 것
			ptr = ptr->next;
		}
		else {
			if (shortest->proc->burst_t > ptr->proc->burst_t) {
				shortest = ptr;
				ptr = ptr->next;
			}
			else {
				ptr = ptr->next;
				/*
				shortest->front->next = shortest->next;
				shortest->next->front = shortest->front;
				q->count--;
				return shortest;
				*/
			}
		}
	}
	if (shortest == q->rear) {
		q->count--;
		return shortest;
	}
	if (shortest == q->head) {
		q->head = shortest->next;
	}
	shortest->front->next = shortest->next;
	shortest->next->front = shortest->front;
	q->count--;
	return shortest;

}


int main(void) {
	_q* q = createQueue(5);
	_q* sjf_q = createQueue(6);
	int curt = 0;
	int* curtp = &curt;
	int pre_fin_t = 0;
	int compare_t = 0;
	_pro* fcfs_arr[5];
	_pro* rr_arr[5];
	_pro* donearr[6];

	// fcfs
	printf("===================================== FCFS ================================ \n \n");

	_pro* temp_f = createP(0);
	temp_f->arr_t = 0;
	q_enqueue(q, temp_f);


	for (int i = 1; i < 5; i++) {
		_pro* temp = createP(i);
		q_enqueue(q, temp);
	}
	q_print_p(q);
	printf("\n ------------------------------- execution start! --------------------------\n");
	for (int i = 0; i < q->size; i++) {
		_elem* myelem = q_retrieve(q);
		simple_exe(myelem->proc, curtp);
		printf("[FCFS] executed: ");
		pprint(myelem->proc);
		fcfs_arr[i] = myelem->proc;
	}

	int avr = get_avr(fcfs_arr, q->size);
	printf("\n------------------------------  FCFS statistics   -------------------------------- \n\n");
	for (int i = 0; i < 5; i++) {
		printf("                         [FCFS] pid: %d   wait_t: %d \n", fcfs_arr[i]->p_no, fcfs_arr[i]->wait_t);
	}
	printf("\n                              avr waiting time : %d \n", avr);
	printf("\n=================================================================================== \n \n");
	printf(" \n\n");

	// experiment
	// 마지막희망.. RR
	_elem* myelem = NULL;
	printf("===================================== ROUND ROBIN ================================ \n \n");
	curt = 0;

	_pro* first = createP(0);
	first->arr_t = 0;
	q_enqueue(q, first);

	for (int i = 1; i < 5; i++) {
		_pro* temp = createP(i);
		q_enqueue(q, temp);
	}
	//q_print_p(q);

	printf("\n--------------------------------- execution start! -------------------------------\n\n");
	while (q->count != 0) {
		myelem = q_retrieve(q);
		rr_exe(q, myelem, curtp);
		printf("[RR] executed: ");
		pprint(myelem->proc);
		rr_arr[myelem->proc->p_no] = myelem->proc;
	}

	printf("\n------------------------------  RR statistics   ----------------------------------- \n\n");
	for (int i = 0; i < 5; i++) {
		printf("                         [RR] pid: %d   wait_t: %d \n", rr_arr[i]->p_no, rr_arr[i]->wait_t);
	}
	printf("\n                             avr waiting time: %d \n", get_avr(rr_arr, q->size));
	printf("\n============================================================================================= \n \n");
	printf(" \n\n");


	printf("================================= SJF (non-premptive) ============================ \n \n");
	curt = 0;

	first = createP(0);
	first->arr_t = 0;
	q_enqueue(sjf_q, first);
	for (int i = 1; i < 6; i++) {
		_pro* proc = createP(i);
		q_enqueue(sjf_q, proc);
	}
	//q_print_p(sjf_q);
	//dequeue 시 신경쓰기
	// head retrieve
	printf("\n --------------------------------- execution start! ------------------------------ \n");
	_elem* ret = q_retrieve(sjf_q);
	simple_exe(ret->proc, curtp);
	printf("[SJF] executed: ");
	pprint(ret->proc);
	compare_t = ret->proc->fin_t;
	donearr[0] = ret->proc;

	// 나머지는 비교가 필요
	for (int j = 1; j < sjf_q->size; j++) {
		_elem* ret = sjf_dequeue(sjf_q, compare_t);
		simple_exe(ret->proc, curtp);
		printf("[SJF] executed: ");
		pprint(ret->proc);
		compare_t = ret->proc->fin_t;
		donearr[j] = ret->proc;
	}
	printf("\n ----------------------------------- execution order ------------------------------\n");
	for (int k = 0; k < 6; k++) {
		pprint(donearr[k]);
	}

	printf("\n ------------------------------------  statistics ----------------------------------\n\n");
	for (int i = 0; i < 5; i++) {
		printf("                         [SJF] pid: %d   wait_t: %d \n", donearr[i]->p_no, donearr[i]->wait_t);
	}
	int avr_wait_t = get_avr(donearr, 6);
	printf(" \n                            average waiting time: %d \n", avr_wait_t);

}