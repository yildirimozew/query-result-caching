#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct QueryNode
{
    char *query;
    struct QueryNode *prev;
    struct QueryNode *next;
} QueryNode;

typedef struct CountNode
{
    int count;
    struct CountNode *prev;
    struct CountNode *next;
    QueryNode **querylist;
} CountNode;

int main() {
  CountNode *head, ct_node, *current, *ct_node_pt, *prev2 = NULL, *prev;
  QueryNode **qrnode_pt_pt, *qrnode_pt, *qrnode_pt2, **qrnode_pt2_pt, **current3_pt, *qrnode_pt3, qr_node, *current2, *current3, *current3_temp, *prev3, *query_table[MAX_SIZE];
  int init_count, i, count, flag=0, flag2=0, new_count, found_count, j, k, flag4 = 0;
  scanf("%d", &init_count);
  for(i=0;i<init_count;i++){
    char *str, *str2;
    str = malloc(6 * sizeof(char));
    scanf(" %s %d", str, &count);
    if(i==0){
      head = malloc(sizeof(CountNode));
      qrnode_pt = malloc(sizeof(QueryNode));
      qrnode_pt_pt = malloc(sizeof(qrnode_pt));
      *qrnode_pt_pt = qrnode_pt;
      qr_node.query = str;
      qr_node.prev = NULL;
      qr_node.next = NULL;
      *qrnode_pt = qr_node;
      ct_node.count = count;
      ct_node.prev = NULL;
      ct_node.next = NULL;
      ct_node.querylist = qrnode_pt_pt;
      *head = ct_node;
    }
    else{
      current = head;
      while(current){
        if(current->count == count){
          current2 = *(current->querylist);
          if(strcmp(str, current2->query) < 0){
            qrnode_pt = malloc(sizeof(QueryNode));
            qrnode_pt_pt = malloc(sizeof(qrnode_pt));
            *qrnode_pt_pt = qrnode_pt;
            qr_node.prev = NULL;
            qr_node.query = str;
            qr_node.next = current2;
            *qrnode_pt = qr_node;
            current2->prev = qrnode_pt;
            current->querylist = qrnode_pt_pt;
            break;
          }
          while(current2){
            if(strcmp(str, current2->query) < 0){
              qrnode_pt = malloc(sizeof(QueryNode));
              qr_node.prev = current2->prev;
              current2->prev->next = qrnode_pt;
              current2->prev = qrnode_pt;
              qr_node.query = str;
              qr_node.next = current2;
              *qrnode_pt = qr_node;
              flag = 1;
              break;
            }
            prev3 = current2;
            current2 = current2->next;
          }
          if(!current2){
            qrnode_pt = malloc(sizeof(QueryNode));
            prev3->next = qrnode_pt;
            qrnode_pt->next = NULL;
            qrnode_pt->prev = prev3;
            qrnode_pt->query = str;
            flag = 1;
          }
          if(flag){
            flag = 0;
            break;
          }
        }
        current = current->next;
      }
      if(!current){
        current = head;
        while(current){
          if(count<current->count){
            prev = current->prev;
            ct_node_pt = malloc(sizeof(CountNode));
            qrnode_pt = malloc(sizeof(QueryNode));
            qrnode_pt_pt = malloc(sizeof(qrnode_pt));
            *qrnode_pt_pt = qrnode_pt;
            ct_node.prev = prev;
            ct_node.next = current;
            ct_node.count = count;
            qr_node.next = NULL;
            qr_node.prev = NULL;
            qr_node.query = str;
            *qrnode_pt = qr_node;
            ct_node.querylist = qrnode_pt_pt;
            *ct_node_pt = ct_node;
            if(prev){
              prev->next = ct_node_pt;
            }else{
              head = ct_node_pt;
            }
            current->prev = ct_node_pt;
            break;
          }
          prev2 = current;
          current = current->next;
        }
        if(!current){
          ct_node_pt = malloc(sizeof(CountNode));
          qrnode_pt = malloc(sizeof(QueryNode));
          qrnode_pt_pt = malloc(sizeof(qrnode_pt));
          str2 = malloc(6 * sizeof(char));
          strcpy(str2, str);
          *qrnode_pt_pt = qrnode_pt;
          ct_node.prev = prev2;
          ct_node.next = NULL;
          ct_node.count = count;
          qr_node.next = NULL;
          qr_node.prev = NULL;
          qr_node.query = str;
          qrnode_pt->next = qr_node.next;
          qrnode_pt->prev = qr_node.prev;
          qrnode_pt->query = str2;
          ct_node.querylist = qrnode_pt_pt;
          *ct_node_pt = ct_node;
          prev2->next = ct_node_pt;
        }
      }
    }
    query_table[i] = qrnode_pt;
  }

  scanf("%d", &new_count);
  for(j=0;j<new_count;j++){
    char* new_str;
    new_str = malloc(6 * sizeof(char));
    scanf("%s", new_str);
    current = head;
    for(i=0;i<init_count;i++){
      current3 = query_table[i];
      current = head;
      if(strcmp(current3->query, new_str) == 0){
        while(current){
          current2 = *(current->querylist);
          while(current2){
            if(strcmp(new_str, current2->query) == 0){
              found_count = current->count;
              flag2 = 1;
              break;
            }
            current2 = current2->next;
          }
          if(flag2){
            flag2 = 0;
            break;
          }
          current = current->next;
        }
        if(current3->prev){
          current3->prev->next = current3->next;
        }else{
          if(current && current3->next){
            *current->querylist = current3->next;
          }else{
            if(current && current->prev){
              current->prev->next = current->next;
              if(current->next){current->next->prev = current->prev;}
            }else if(current){
              if(current->next){
                current->next->prev = NULL;
                }else{
                  head = NULL;
                }
              head = current->next;
            }
          }
        }
        if(current3->next){
          current3->next->prev = current3->prev;
        }
        current = head;
        while(current){
          if(current->count == found_count + 1){
            current2 = *(current->querylist);
            while(current2){
              if(strcmp(new_str, current2->query) < 0){
                current3->next = current2;
                current3->prev = current2->prev;
                if(current2->prev){
                  current2->prev->next = current3;
                }else{
                  current3_pt = malloc(sizeof(current3));
                  *current3_pt = current3;
                  current->querylist = current3_pt;
                }
                current2->prev = current3;
                flag = 1;
                flag2 = 1;
                break;
            }
              prev3 = current2;
              current2 = current2->next;
            }
            if(!current2){
              current3->next = NULL;
              current3->prev = prev3;
              prev3->next = current3;
              flag = 1;
              break;
            }
          }
          if(flag){
            flag = 0;
            break;}
          current = current->next;
        }
        if(!current){
          current = head;
          while(current){
          if(found_count + 1<current->count){
            ct_node_pt = malloc(sizeof(CountNode));
            qrnode_pt2 = malloc(sizeof(QueryNode));
            qrnode_pt2_pt = malloc(sizeof(qrnode_pt2));
            *qrnode_pt2_pt = qrnode_pt2;
            ct_node_pt->prev = current->prev;
            ct_node_pt->next = current;
            ct_node_pt->count = found_count + 1;
            qrnode_pt2->next = NULL;
            qrnode_pt2->prev = NULL;
            qrnode_pt2->query = new_str;
            ct_node_pt->querylist = qrnode_pt2_pt;
            query_table[i] = qrnode_pt2;
            if(current->prev){
              current->prev->next = ct_node_pt;
            }else{
              head = ct_node_pt;
            }
            current->prev = ct_node_pt;
            flag = 1;
            break;
          }
          prev2 = current;
          current = current->next;
        }
        if(flag || flag2){
          flag = 0;
          flag2 = 0;
          break;
        }
        if(!current){
          current3_pt = malloc(sizeof(current3));
          ct_node_pt = malloc(sizeof(CountNode));/*!!!!!!!!!!!!!!!!!!*/
          ct_node.prev = prev2;
          ct_node.next = NULL;
          ct_node.count = found_count + 1;
          current3->prev = NULL;
          current3->next = NULL;
          *current3_pt = current3;
          ct_node.querylist = current3_pt;
          *ct_node_pt = ct_node;
          if(prev2){
            prev2->next = ct_node_pt;
            }else{
              head = ct_node_pt;
            }
          flag = 1;
        }
        }
      }
      if(flag || flag2){
        flag = 0;
        flag2 = 0;
        break;
      }
    }
    if(i==init_count){
      if(MAX_SIZE > init_count){
        qrnode_pt = malloc(sizeof(QueryNode));
        qrnode_pt->query = new_str;
        init_count++;
        query_table[i] = qrnode_pt;
        if(head->count == 1){
          current2 = *(head->querylist);
          while(current2){
            if(strcmp(new_str, current2->query) < 0){
              if(current2 == *(head->querylist)){
                *(head->querylist) = qrnode_pt;
              }
              qrnode_pt->next = current2;
              if(current2->prev){
                current2->prev->next = qrnode_pt;
              }
              qrnode_pt->prev = current2->prev;
              current2->prev = qrnode_pt;
              break;
            }
            if(flag){
              flag = 0;
              break;
            }
            prev3 = current2;
            current2 = current2->next;
          }
          if(!current2){
            qrnode_pt->next = NULL;
            qrnode_pt->prev = prev3;
            prev3->next = qrnode_pt;
          }
        }else{
          ct_node_pt = malloc(sizeof(CountNode));
          qrnode_pt_pt = malloc(sizeof(qrnode_pt));
          *qrnode_pt_pt = qrnode_pt;
          qr_node.query = new_str;
          qr_node.prev = NULL;
          qr_node.next = NULL;
          *qrnode_pt = qr_node;
          ct_node.querylist = qrnode_pt_pt;
          ct_node.count = 1;
          ct_node.prev = NULL;
          ct_node.next = head;
          *ct_node_pt = ct_node;
          head->prev = ct_node_pt;
          head = ct_node_pt;
        }
      }else{
        char *str3;
        str3 = malloc(6 * sizeof(char));
        str3 = (*(head->querylist))->query;
        if((*(head->querylist))->next){
          (*(head->querylist))->next->prev = NULL;
        }else{
          if(!((*(head->querylist))->prev)){
            current = head;
            while(current){
              if((*(current->querylist))->query == str3){
                if(current->prev){
                  current->prev->next = current->next;
                  if(current->next){
                    current->next->prev = current->prev;
                  }
                  break;
                }else if(current->next){
                  current->next->prev = NULL;
                  head = current->next;
                  flag4 = 1;
                  break;
                }
              }
              current = current->next;
            }
          }
        }
        if(!flag4){
          head->querylist = &((*(head->querylist))->next);
        }
        flag4 = 0;
        qrnode_pt3 = malloc(sizeof(QueryNode));
        qrnode_pt3->query = new_str;
        for(k=0;k<init_count;k++){
          if(strcmp(query_table[k]->query, str3) == 0){
            query_table[k] = qrnode_pt3;
            break;
          }
        }
        if(head->count == 1){
          current2 = *(head->querylist);
          while(current2){
            if(strcmp(new_str, current2->query) < 0){
              if(current2 == *(head->querylist)){
                *(head->querylist) = qrnode_pt3;
              }
              qrnode_pt3->next = current2;
              qrnode_pt3->prev = current2->prev;
              if(current2->prev){
                current2->prev->next = qrnode_pt3;
              }
              current2->prev = qrnode_pt3;
              break;
            }
            if(flag){
              flag = 0;
              break;
            }
            prev3 = current2;
            current2 = current2->next;
          }
          if(!current2){
            qrnode_pt3->next = NULL;
            qrnode_pt3->prev = prev3;
            prev3->next = qrnode_pt3;
          }
        }else{
          ct_node_pt = malloc(sizeof(CountNode));
          qrnode_pt_pt = malloc(sizeof(qrnode_pt));
          *qrnode_pt_pt = qrnode_pt3;
          qrnode_pt3->prev = NULL;
          qrnode_pt3->next = NULL;
          ct_node.querylist = qrnode_pt_pt;
          ct_node.count = 1;
          ct_node.prev = NULL;
          ct_node.next = head;
          *ct_node_pt = ct_node;
          head->prev = ct_node_pt;
          head = ct_node_pt;
        }
      }
    }
  }

  current = head;
  while(current){
    printf("%d ",current->count);
    current2 = *(current->querylist);
    while(current2){
      printf("%s",current2->query);
      if(current2->next){
        printf(" ");
      }else{
        printf("\n");
      }
      current2 = current2->next;
    }
    current = current->next;
  }
}