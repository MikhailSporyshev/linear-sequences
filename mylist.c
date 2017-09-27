#include <stdlib.h>
#include <stdio.h>
#include "linear_sequence.h"
 
typedef struct node {
    LSQ_BaseTypeT data;
    struct node* left;
    struct node* right;
}node;
 
typedef struct iter{
    node* nodePtr;
}iter;
 
typedef struct MyList {
    node* start;
    node* end;
}MyList;
 
/* Р¤СѓРЅРєС†РёСЏ, СЃРѕР·РґР°СЋС‰Р°СЏ РїСѓСЃС‚РѕР№ РєРѕРЅС‚РµР№РЅРµСЂ. Р’РѕР·РІСЂР°С‰Р°РµС‚ РЅР°Р·РЅР°С‡РµРЅРЅС‹Р№ РµРјСѓ РґРµСЃРєСЂРёРїС‚РѕСЂ */
extern LSQ_HandleT LSQ_CreateSequence(void) {
    MyList* ptrList = malloc(sizeof(MyList));
    ptrList->start = malloc(sizeof(node));
    ptrList->end = malloc(sizeof(node));
     
    ptrList->start->right = ptrList->end;
    ptrList->end->left = ptrList->start; 
     
    ptrList->start->left = NULL;
    ptrList->end->right = NULL;
 
    return ptrList;
}
/*
static void LSQ_DisplaySequence(LSQ_HandleT handle) {
    printf("%s", "LSQ_DisplaySequence\n");
    LSQ_IteratorT displayIterator = LSQ_GetFrontElement(handle);
    while(!LSQ_IsIteratorPastRear(displayIterator)) {
        printf("%d ", *LSQ_DereferenceIterator(displayIterator));
        LSQ_AdvanceOneElement(displayIterator);
    }   
    printf("%s", "LSQ_DisplaySequence complited\n");
}*/
 
/* Р¤СѓРЅРєС†РёСЏ, СѓРЅРёС‡С‚РѕР¶Р°СЋС‰Р°СЏ РєРѕРЅС‚РµР№РЅРµСЂ СЃ Р·Р°РґР°РЅРЅС‹Рј РґРµСЃРєСЂРёРїС‚РѕСЂРѕРј. РћСЃРІРѕР±РѕР¶РґР°РµС‚ РїСЂРёРЅР°РґР»РµР¶Р°С‰СѓСЋ РµРјСѓ РїР°РјСЏС‚СЊ */
extern void LSQ_DestroySequence(LSQ_HandleT handle) {
    if(handle != NULL) { 
        MyList* ptrList = (MyList*)handle;
        node* ptrNode = ptrList->start->right;
        while(ptrNode->right != NULL) {
            ptrNode = ptrNode->right;
            free(ptrNode->left);
        }
        free(ptrList->start);
        free(ptrList->end);
        free(ptrList);
        handle = LSQ_HandleInvalid;
    }
}
 
/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ С‚РµРєСѓС‰РµРµ РєРѕР»РёС‡РµСЃС‚РІРѕ СЌР»РµРјРµРЅС‚РѕРІ РІ РєРѕРЅС‚РµР№РЅРµСЂРµ */
extern LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle) {
    if(handle != NULL) { 
        MyList* ptrList = (MyList*)handle;
        node* ptrNode = ptrList->start;
        int i;
        i = 0;
        while(ptrNode->right != ptrList->end) {
            ptrNode = ptrNode->right;
            i = i + 1;
        }
        return i;
    }
    return 0;
}
 
/* Р¤СѓРЅРєС†РёСЏ, РѕРїСЂРµРґРµР»СЏСЋС‰Р°СЏ, РјРѕР¶РµС‚ Р»Рё РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ Р±С‹С‚СЊ СЂР°Р·С‹РјРµРЅРѕРІР°РЅ */
extern int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator) {
    if(iterator != NULL) {
        node* ptrNode = ((iter*)iterator)->nodePtr;
        if(ptrNode != NULL) {
            if((ptrNode->left != NULL) && (ptrNode->right != NULL)) {
                return 1;
            }
        }
    }
    return 0;
 
}
/* Р¤СѓРЅРєС†РёСЏ, РѕРїСЂРµРґРµР»СЏСЋС‰Р°СЏ, СѓРєР°Р·С‹РІР°РµС‚ Р»Рё РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ РЅР° СЌР»РµРјРµРЅС‚, СЃР»РµРґСѓСЋС‰РёР№ Р·Р° РїРѕСЃР»РµРґРЅРёРј РІ РєРѕРЅС‚РµР№РЅРµСЂРµ */
extern int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator) {
    /*printf("%s", "LSQ_IsIteratorPastRear\n");*/
    if(iterator != NULL) { 
        node* ptrNode = ((iter*)iterator)->nodePtr->right;
        return(ptrNode == NULL);
    }
    return 0;
}
/* Р¤СѓРЅРєС†РёСЏ, РѕРїСЂРµРґРµР»СЏСЋС‰Р°СЏ, СѓРєР°Р·С‹РІР°РµС‚ Р»Рё РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ РЅР° СЌР»РµРјРµРЅС‚, РїСЂРµРґС€РµСЃС‚РІСѓСЋС‰РёР№ РїРµСЂРІРѕРјСѓ РІ РєРѕРЅС‚РµР№РЅРµСЂРµ */
extern int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator) {
    /*printf("%s", "LSQ_IsIteratorBeforeFirst\n");*/
    if(iterator != NULL) { 
        node* ptrNode = ((iter*)iterator)->nodePtr->left;
        return(ptrNode == NULL); 
    }
    return 0;
}
 
/* Р¤СѓРЅРєС†РёСЏ, СЂР°Р·С‹РјРµРЅРѕРІС‹РІР°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ. Р’РѕР·РІСЂР°С‰Р°РµС‚ СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЌР»РµРјРµРЅС‚, РЅР° РєРѕС‚РѕСЂС‹Р№ СЃСЃС‹Р»Р°РµС‚СЃСЏ РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ */
extern LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator) {
    if(iterator != NULL) { 
        return(&((iter*)iterator)->nodePtr->data);
    }
    return NULL;
}
 
 
static LSQ_IteratorT LSQ_GetBeforeFirstElement(LSQ_HandleT handle) {
    /*printf("%s", "LSQ_GetFrontElement\n");*/
    if(handle != NULL) {
        MyList* listPtr = (MyList*)handle;
        iter* iterPtr = malloc(sizeof(iter));
        iterPtr->nodePtr = listPtr->start;
        /*printf("%s", "LSQ_GetFrontElement complited\n");*/
        return iterPtr;
    }
    return NULL; 
}
 
/* РЎР»РµРґСѓСЋС‰РёРµ С‚СЂРё С„СѓРЅРєС†РёРё СЃРѕР·РґР°СЋС‚ РёС‚РµСЂР°С‚РѕСЂ РІ РїР°РјСЏС‚Рё Рё РІРѕР·РІСЂР°С‰Р°СЋС‚ РµРіРѕ РґРµСЃРєСЂРёРїС‚РѕСЂ */
/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° СЌР»РµРјРµРЅС‚ СЃ СѓРєР°Р·Р°РЅРЅС‹Рј РёРЅРґРµРєСЃРѕРј */
extern LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index) {
    if(handle != NULL) { 
        MyList* ptrList = (MyList*)handle;
        iter* iterator = malloc(sizeof(iter));
        iterator->nodePtr = ptrList->start->right;
        int i = 0;
        while((!LSQ_IsIteratorPastRear(iterator))&&(i < index)) {
            LSQ_AdvanceOneElement(iterator);
            i = i + 1;
        }
        return iterator;
    }
    return NULL;
}
 
 
/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° РїРµСЂРІС‹Р№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
extern LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle) {
    /*printf("%s", "LSQ_GetFrontElement\n");*/
    if(handle != NULL) { 
        MyList* listPtr = (MyList*)handle;
        iter* iterPtr = malloc(sizeof(iter));
        iterPtr->nodePtr = listPtr->start->right;
        /*printf("%s", "LSQ_GetFrontElement complited\n");*/
        return iterPtr;
    }
    return NULL;
}
 
/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° РїРѕСЃР»РµРґРЅРёР№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР°*/
static LSQ_IteratorT LSQ_GetRearElement(LSQ_HandleT handle) {
    /*printf("%s", "LSQ_GetRearElement\n");*/
    if(handle != NULL) {  
        MyList* someList = (MyList*)handle;
        iter* iterator = malloc(sizeof(iter));
        iterator->nodePtr = someList->end->left;
        /*printf("%s", "LSQ_GetFrontElement complited\n");*/
        return iterator;
    }
    return NULL;
}
 
 
/* Р¤СѓРЅРєС†РёСЏ, РІРѕР·РІСЂР°С‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ, СЃСЃС‹Р»Р°СЋС‰РёР№СЃСЏ РЅР° СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° СЃР»РµРґСѓСЋС‰РёР№ Р·Р° РїРѕСЃР»РµРґРЅРёРј */
extern LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle) {
    /*printf("%s", "LSQ_GetPastRearElement\n");*/
    if(handle != NULL) { 
        MyList* someList = (MyList*)handle;
        iter* iterator = malloc(sizeof(iter));
        iterator->nodePtr = someList->end;
        /*printf("%s", "LSQ_GetPastRearElement complited\n");*/
        return iterator;
    }
    return NULL;
}
 
/* Р¤СѓРЅРєС†РёСЏ, СѓРЅРёС‡С‚РѕР¶Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ СЃ Р·Р°РґР°РЅРЅС‹Рј РґРµСЃРєСЂРёРїС‚РѕСЂРѕРј Рё РѕСЃРІРѕР±РѕР¶РґР°СЋС‰Р°СЏ РїСЂРёРЅР°РґР»РµР¶Р°С‰СѓСЋ РµРјСѓ РїР°РјСЏС‚СЊ */
extern void LSQ_DestroyIterator(LSQ_IteratorT iterator) {
    if(iterator != NULL) { 
        free(iterator);
    }
}
 
/* Р¤СѓРЅРєС†РёСЏ, РїРµСЂРµРјРµС‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° РѕРґРёРЅ СЌР»РµРјРµРЅС‚ РІРїРµСЂРµРґ */
extern void LSQ_AdvanceOneElement(LSQ_IteratorT iterator) {
    if(iterator != NULL) {  
        iter* iterPtr = (iter*)iterator; 
        iterPtr->nodePtr = iterPtr->nodePtr->right;
    }
}
/* Р¤СѓРЅРєС†РёСЏ, РїРµСЂРµРјРµС‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° РѕРґРёРЅ СЌР»РµРјРµРЅС‚ РЅР°Р·Р°Рґ */
extern void LSQ_RewindOneElement(LSQ_IteratorT iterator) {  
    if(iterator != NULL) { 
        iter* iterPtr = (iter*)iterator;
        iterPtr->nodePtr = iterPtr->nodePtr->left;
    }
}
/* Р¤СѓРЅРєС†РёСЏ, РїРµСЂРµРјРµС‰Р°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° Р·Р°РґР°РЅРЅРѕРµ СЃРјРµС‰РµРЅРёРµ СЃРѕ Р·РЅР°РєРѕРј*/
extern void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift) {
    if(iterator != NULL) { 
        int i = 0;
        if(shift > 0) {
            while((!LSQ_IsIteratorPastRear(iterator)) && (i < shift)) {
                LSQ_AdvanceOneElement(iterator);
                i = i + 1;
            }
        }
        if(shift < 0) {
            while((!LSQ_IsIteratorBeforeFirst(iterator)) && (i > shift)) {
                LSQ_RewindOneElement(iterator);
                i = i - 1;
            }
        }
    }
}
 
 
/* Р¤СѓРЅРєС†РёСЏ, СѓСЃС‚Р°РЅР°РІР»РёРІР°СЋС‰Р°СЏ РёС‚РµСЂР°С‚РѕСЂ РЅР° СЌР»РµРјРµРЅС‚ СЃ СѓРєР°Р·Р°РЅРЅС‹Рј РЅРѕРјРµСЂРѕРј */
extern void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos) {
    if(iterator != NULL) { 
        while(!LSQ_IsIteratorBeforeFirst(iterator)) {
            LSQ_RewindOneElement(iterator);
        }
        int i = 0;
        while((!LSQ_IsIteratorPastRear(iterator)) && (i <= pos)) {
            LSQ_AdvanceOneElement(iterator);
            i = i + 1;
        }
    }
}
 
/* Р¤СѓРЅРєС†РёСЏ, РґРѕР±Р°РІР»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РІ РЅР°С‡Р°Р»Рѕ РєРѕРЅС‚РµР№РЅРµСЂР° */
extern void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    /*printf("%s", "LSQ_InsertFrontElement\n");*/
    if(handle != NULL) { 
        LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
        LSQ_InsertElementBeforeGiven(iterator, element);
        LSQ_DestroyIterator(iterator);
        /*printf("%s", "LSQ_InsertFrontElement complited\n");*/
    }
}
/* Р¤СѓРЅРєС†РёСЏ, РґРѕР±Р°РІР»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РІ РєРѕРЅРµС† РєРѕРЅС‚РµР№РЅРµСЂР° */
extern void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    if(handle != NULL) {
        LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
        LSQ_InsertElementBeforeGiven(iterator, element);
        LSQ_DestroyIterator(iterator);
    }
}
/* Р¤СѓРЅРєС†РёСЏ, РґРѕР±Р°РІР»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РІ РєРѕРЅС‚РµР№РЅРµСЂ РЅР° РїРѕР·РёС†РёСЋ, СѓРєР°Р·С‹РІР°РµРјСѓСЋ РІ РґР°РЅРЅС‹Р№ РјРѕРјРµРЅС‚ РёС‚РµСЂР°С‚РѕСЂРѕРј.         */
/* Р­Р»РµРјРµРЅС‚, РЅР° РєРѕС‚РѕСЂС‹Р№ СѓРєР°Р·С‹РІР°РµС‚ РёС‚РµСЂР°С‚РѕСЂ, Р° С‚Р°РєР¶Рµ РІСЃРµ РїРѕСЃР»РµРґСѓСЋС‰РёРµ, СЃРґРІРёРіР°РµС‚СЃСЏ РЅР° РѕРґРЅСѓ РїРѕР·РёС†РёСЋ РІ РєРѕРЅРµС†. */
/* Р—Р°РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ РїСЂРѕРґРѕР»Р¶Р°РµС‚ СѓРєР°Р·С‹РІР°С‚СЊ РЅР° СЌР»РµРјРµРЅС‚ РїРѕСЃР»РµРґРѕРІР°С‚РµР»СЊРЅРѕСЃС‚Рё СЃ С‚РµРј Р¶Рµ РёРЅРґРµРєСЃРѕРј.              */
extern void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement) {
    /*printf("%s", "LSQ_InsertElementBeforeGiven\n");
    */
    if(iterator != NULL) {
        node* newNodePtr = malloc(sizeof(node));
        iter* iterPtr = (iter*)iterator;
        node* iterNodePtr = iterPtr->nodePtr;
         
        newNodePtr->data = newElement;
 
        newNodePtr->left = iterPtr->nodePtr->left;
        newNodePtr->right = iterPtr->nodePtr;
 
        iterPtr->nodePtr->left->right = newNodePtr;
        iterPtr->nodePtr->left = newNodePtr;
 
        iterPtr->nodePtr = newNodePtr;
 
        /*printf("%s", "LSQ_InsertElementBeforeGiven complited\n");*/
    }
}
 
/* Р¤СѓРЅРєС†РёСЏ, СѓРґР°Р»СЏСЋС‰Р°СЏ РїРµСЂРІС‹Р№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
extern void LSQ_DeleteFrontElement(LSQ_HandleT handle) {
    if(handle != NULL) {
        LSQ_DeleteGivenElement(LSQ_GetFrontElement(handle));
    }
}
/* Р¤СѓРЅРєС†РёСЏ, СѓРґР°Р»СЏСЋС‰Р°СЏ РїРѕСЃР»РµРґРЅРёР№ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР° */
extern void LSQ_DeleteRearElement(LSQ_HandleT handle) {
    if(handle != NULL) { 
        LSQ_DeleteGivenElement(LSQ_GetRearElement(handle));
    }
}
/* Р¤СѓРЅРєС†РёСЏ, СѓРґР°Р»СЏСЋС‰Р°СЏ СЌР»РµРјРµРЅС‚ РєРѕРЅС‚РµР№РЅРµСЂР°, СѓРєР°Р·С‹РІР°РµРјС‹Р№ Р·Р°РґР°РЅРЅС‹Рј РёС‚РµСЂР°С‚РѕСЂРѕРј.                 */
/* Р’СЃРµ РїРѕСЃР»РµРґСѓСЋС‰РёРµ СЌР»РµРјРµРЅС‚С‹ СЃРјРµС‰Р°СЋС‚СЃСЏ РЅР° РѕРґРЅСѓ РїРѕР·РёС†РёСЋ РІ СЃС‚РѕСЂРѕРЅСѓ РЅР°С‡Р°Р»Р°.                    */
/* Р—Р°РґР°РЅРЅС‹Р№ РёС‚РµСЂР°С‚РѕСЂ РїСЂРѕРґРѕР»Р¶Р°РµС‚ СѓРєР°Р·С‹РІР°С‚СЊ РЅР° СЌР»РµРјРµРЅС‚ РїРѕСЃР»РµРґРѕРІР°С‚РµР»СЊРЅРѕСЃС‚Рё СЃ С‚РµРј Р¶Рµ РёРЅРґРµРєСЃРѕРј. */
extern void LSQ_DeleteGivenElement(LSQ_IteratorT iterator) {
    if(LSQ_IsIteratorDereferencable(iterator)) {
        iter* iterPtr = (iter*)iterator;
        node* ptrNode = ((iter*)iterator)->nodePtr;
        ptrNode->left->right = ptrNode->right;
        ptrNode->right->left = ptrNode->left;
        iterPtr->nodePtr = iterPtr->nodePtr->right;
        free(ptrNode);
    }
}
/*
int main(void) {
    LSQ_HandleT handle;
    LSQ_IteratorT iter;
    int size, el;
 
    handle = LSQ_CreateSequence();
    LSQ_InsertFrontElement(handle, 33);
    LSQ_InsertFrontElement(handle, 32);
 
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_InsertRearElement(handle, 20);
    LSQ_InsertRearElement(handle, 21);
 
 
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_DeleteRearElement(handle);
 
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_DeleteFrontElement(handle);
 
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
     
    iter = LSQ_GetElementByIndex(handle, 1);
    LSQ_InsertElementBeforeGiven(iter, 76);
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_InsertElementBeforeGiven(iter, 54);
    LSQ_InsertElementBeforeGiven(iter, 100);
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_AdvanceOneElement(iter);
    LSQ_AdvanceOneElement(iter);
    LSQ_RewindOneElement(iter);
    LSQ_DeleteGivenElement(iter);
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_ShiftPosition(iter, 1);
    LSQ_InsertElementBeforeGiven(iter, 0);
    size = LSQ_GetSize(handle);
    printf("%s %d ", "size", size);
    printf("%s", "\n");
 
    LSQ_DisplaySequence(handle);
    printf("%s", "\n");
 
    LSQ_DestroyIterator(iter);
    iter = LSQ_GetPastRearElement(handle);
    if(LSQ_IsIteratorPastRear(iter)) {
        printf("%s", "iterator past rear\n");
    }
 
 
    LSQ_DestroyIterator(iter);
    iter = LSQ_GetFrontElement(handle);
    LSQ_RewindOneElement(iter);
    if(LSQ_IsIteratorBeforeFirst(iter)) {
        printf("%s", "iterator before first\n");
    }
    if(LSQ_IsIteratorDereferencable(iter)) {
        printf("%s", "iterator dereferencable");
    }
 
    return 0;
}*/
