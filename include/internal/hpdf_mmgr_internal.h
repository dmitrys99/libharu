#ifndef HPDF_MMGR_INTERNAL_H
#define HPDF_MMGR_INTERNAL_H

typedef struct  _HPDF_MPool_Node_Rec {
    HPDF_BYTE*       buf;
    HPDF_UINT        size;
    HPDF_UINT        used_size;
    HPDF_MPool_Node  next_node;
} HPDF_MPool_Node_Rec;

#endif /* HPDF_MMGR_INTERNAL_H */