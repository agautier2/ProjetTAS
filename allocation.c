#include "allocation.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include <time.h>


void buffer_tracker_print(void){
    
    double_linked_list *temp = buffer_tracker;
    while(temp != NULL){
        printf("[%ld][%d][%c]→ ",(char*)temp->ptr-(char*)heap,temp->size,temp->filled);
        temp=temp->next; 
           
    }
    printf("\n");
}


void ecrire_date_heure_adresse(void* ptr, int size)
{

  // Ouverture du fichier en mode écriture
  FILE * fp = fopen("allocation.txt", "a");

  if (fp == NULL) {
    printf("Impossible d'ouvrir le fichier.\n");
    return;
  }

  // Obtention de la date et de l'heure actuelles
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char s[64];
  strftime(s, sizeof(s), "%c", tm);

  // Écriture de la date, de l'heure, de l'adresse du pointeur et de la taille dans le fichier
  fprintf(fp, "[%s] malloced %d byte at adress %p\n", s,size, (void*) ptr);
  // Fermeture du fichier
  fclose(fp);
}

void init_heap(void){
	
    heap = malloc(SIZE_HEAP);
    if(heap==NULL){
        exit(0);
    }
    buffer_tracker = d_ll_get_new_elem(heap,SIZE_HEAP,BUFF_FREE);
    if(buffer_tracker==NULL){
        exit(0);
    }
	//strategy = &first_fit; // By default the strategy is first_fit
    
    
}

void free_heap(void){
    free(heap);
    d_ll_free(buffer_tracker);

}

void* heap_malloc(unsigned int size){
    
    double_linked_list *temp = buffer_tracker;
    while(temp != NULL){
        if(temp->size==size && temp->filled==BUFF_FREE){
            temp->filled=BUFF_FILLED;
            ecrire_date_heure_adresse(temp,size);
            return temp->ptr;
        }
        else if(temp->size>size && temp->filled==BUFF_FREE){
            double_linked_list *new_elem = d_ll_get_new_elem((char*) temp->ptr+size,temp->size-size,BUFF_FREE);
            temp->size = size;
            temp->filled = BUFF_FILLED;
        
            if(temp->next){
                double_linked_list *temp_next = temp->next;
                temp->next = new_elem;
                new_elem->prev = temp;
                temp_next->prev = new_elem;
                new_elem->next = temp_next;
            }
            else{
                d_ll_push_elem(temp,new_elem);
            }
            ecrire_date_heure_adresse(new_elem,size);
            return temp->ptr;
            
        }
        temp=temp->next;
        
    }
    
    
    return NULL;
}
    

#include <stdio.h>
#include <time.h>


