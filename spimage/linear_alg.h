#ifndef _LINEAR_ALG_H_
#define _LINEAR_ALG_H_ 1

#include <stdio.h>
#include <complex.h>
#include <string.h>
#include <math.h>

typedef struct{
  unsigned int size;
  real * data;
} sp_vector;

typedef struct{
  unsigned int size;
  Complex * data;
} sp_cvector;


typedef struct{
  unsigned int rows;
  unsigned int cols;
  real * data;
} sp_matrix;

typedef struct{
  unsigned int rows;
  unsigned int cols;
  int * data;
} sp_imatrix;


typedef struct{
  unsigned int rows;
  unsigned int cols;
  Complex * data;
} sp_cmatrix;


static inline real sp_min(real a,real b){
  if(a< b){
    return a;
  }
  return b;
}

static inline real sp_max(real a,real b){
  if(a > b){
    return a;
  }
  return b;
}

#define sp_swap(a,b,t){ t _temp = a; a = b;b = _temp}



/*! This function allocates memory for a matrix of size nrows rows by ncols columns and initializes all the elements of the matrix to zero.
 *
 */
spimage_EXPORT sp_matrix * sp_matrix_alloc(unsigned int nrows, unsigned int ncols);

/*! This function allocates memory for a Complex matrix of size nrows rows by ncols columns and initializes all the elements of the matrix to zero.
 *
 */
spimage_EXPORT sp_cmatrix * sp_cmatrix_alloc(unsigned int nrows, unsigned int ncols);


/*! This function creates a duplicate of it's argument and returns a pointer to it
 *
 */
spimage_EXPORT sp_cmatrix * sp_cmatrix_duplicate(sp_cmatrix * m);

/*! This function allocates memory for an Integer matrix of size nrows rows by ncols columns and initializes all the elements of the matrix to zero.
 *
 */
spimage_EXPORT sp_imatrix * sp_imatrix_alloc(unsigned int nrows, unsigned int ncols);

/*! This function frees a previously allocated matrix m
 *
 */
spimage_EXPORT void sp_matrix_free(sp_matrix * m);

/*! This function frees a previously allocated Complex matrix m
 *
 */
spimage_EXPORT void sp_cmatrix_free(sp_cmatrix * m);

/*! This function frees a previously allocated Complex matrix m
 *
 */
spimage_EXPORT void sp_imatrix_free(sp_imatrix * m);


/*! Creates an empty zero initialized vector of the desired size.
 *
 * This function creates a vector of length n, returning a pointer
 * to a newly initialized vector struct. All vector elements are set
 * to 0.
 */
spimage_EXPORT sp_vector * sp_vector_alloc(const int size);

/*! Creates an empty zero initialized Complex vector of the desired size.
 *
 * This function creates a vector of length n, returning a pointer
 * to a newly initialized vector struct. All vector elements are set
 * to 0.
 */
spimage_EXPORT sp_cvector * sp_cvector_alloc(const int size);

/*! Frees a previously allocated vector.
 *
 */
spimage_EXPORT void sp_vector_free(sp_vector * v);

/*! Frees a previously allocated Complex vector.
 *
 */
spimage_EXPORT void sp_cvector_free(sp_cvector * v);


/*! This function returns the size of the vector v
 *
 */
static inline unsigned int sp_vector_size(const sp_vector * v){
  return v->size;   
}

/*! This function returns the size of the Complex vector v
 *
 */
static inline unsigned int sp_cvector_size(const sp_cvector * v){
  return v->size;   
}

/*! This function returns the (row,col)-th element of a matrix m.
 *
 * Row and col must lie in the range of 0 to nrows-1 and 0 to ncols-1.
 */
static inline real sp_matrix_get (const sp_matrix * m, unsigned int row, unsigned int col){
  return m->data[col*m->rows+row];
}

/*! This function returns the (row,col)-th element of an Integer matrix m.
 *
 * row and col must lie in the range of 0 to nrows-1 and 0 to ncols-1.
 */
static inline int sp_imatrix_get (const sp_imatrix * m, unsigned int row, unsigned int col){
  return m->data[col*m->rows+row];
}


/*! This function returns the (row,col)-th element of a Complex matrix m.
 *
 * row and col must lie in the range of 0 to nrows-1 and 0 to ncols-1.
 */
static inline Complex sp_cmatrix_get (const sp_cmatrix * m, unsigned int row, unsigned int col){
  return m->data[col*m->rows+row];
}

/*! This function sets the (row,col)-th element of a matrix m to x.
 *
 * row and col must lie in the range of 0 to nrows-1 and 0 to ncols-1.
 */
static inline void sp_matrix_set (sp_matrix * m, unsigned int row, unsigned int col, real x){
  m->data[col*m->rows+row] = x;
}

/*! This function sets the (row,col)-th element of an Integer matrix m to x.
 *
 * row and col must lie in the range of 0 to nrows-1 and 0 to ncols-1.
 */
static inline void sp_imatrix_set (sp_imatrix * m, unsigned int row, unsigned int col, int n){
  m->data[col*m->rows+row] = n;
}

/*! This function sets the (row,col)-th element of a Complex matrix m to x.
 *
 * row and col must lie in the range of 0 to nrows-1 and 0 to ncols-1.
 */
static inline void sp_cmatrix_set (sp_cmatrix * m, unsigned int row, unsigned int col, Complex x){
  m->data[col*m->rows+row] = x;
}


/*! This function returns the nth element of a vector v.
 *
 * n must be in the range of 0 to size-1.
 */
static inline real sp_vector_get (const sp_vector * v, unsigned int n){
  return v->data[n];
}

/*! This function returns the the nth element of a Complex vector v.
 *
 * n must be in the range of 0 to size-1.
 */
static inline Complex sp_cvector_get(const sp_cvector * v, unsigned int n){
  return v->data[n];
}

/*! This function sets the nth element of a vector v to x.
 *
 * n must be in the range of 0 to size-1.
 */
static inline void sp_vector_set (const sp_vector * v, unsigned int n, real x){
  v->data[n] = x;
}

/*! This function sets the nth element of a Complex vector v to x.
 *
 * n must be in the range of 0 to size-1.
 */
static inline void sp_cvector_set (const sp_cvector * v, unsigned int n, Complex x){
  v->data[n] = x;
}

/*! This function copies the elements of the matrix b into the matrix a. 
  *
  * The two matrices must have the same dimensions.
  */
static inline void sp_matrix_memcpy(sp_matrix * dest, const sp_matrix * src){
  int i;
  if(src->rows*src->cols < 1024){
    /* avoid function call and make inline possibly useful */
    for(i = 0;i<src->rows*src->cols;i++){
      dest->data[i] = src->data[i];
    }
  }else{
    memcpy(dest->data,src->data,sizeof(real)*src->rows*src->cols);
  }
}


/*! This function copies the elements of the integer matrix b into the integer matrix a. 
  *
  * The two matrices must have the same dimensions.
  */
static inline void sp_imatrix_memcpy(sp_imatrix * dest, const sp_imatrix * src){
  int i;
  if(src->rows*src->cols < 1024){
    /* avoid function call and make inline possibly useful */
    for(i = 0;i<src->rows*src->cols;i++){
      dest->data[i] = src->data[i];
    }
  }else{
    memcpy(dest->data,src->data,sizeof(int)*src->rows*src->cols);
  }
}


/*! This function copies the elements of the Complex matrix b into the Complex matrix a. 
  *
  * The two matrices must have the same dimensions.
  */
static inline void sp_cmatrix_memcpy(sp_cmatrix * dest, const sp_cmatrix * src){
  int i;
  if(src->rows*src->cols < 1024){
    /* avoid function call and make inline possibly useful */
    for(i = 0;i<src->rows*src->cols;i++){
      dest->data[i] = src->data[i];
    }
  }else{
    memcpy(dest->data,src->data,sizeof(Complex)*src->rows*src->cols);
  }
}


/*! This function adds the elements of vector b to the elements of vector a, a'_i = a_i + b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_vector_add(sp_vector * a, const sp_vector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] += b->data[i];
  }
}


/*! This function adds the elements of a Complex vector b to the elements of a Complex vector a, a'_i = a_i + b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_cvector_add(sp_cvector * a, const sp_cvector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] += b->data[i];
  }
}

/*! This function subtracts the elements of vector b to the elements of vector a, a'_i = a_i - b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_vector_sub(sp_vector * a, const sp_vector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] -= b->data[i];
  }
}


/*! This function subtracts the elements of Complex vector b to the elements of Complex vector a, a'_i = a_i - b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_cvector_sub(sp_cvector * a, const sp_cvector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] -= b->data[i];
  }
}

/*! This function mutiplies the elements of vector a with the elements of vector b, a'_i = a_i * b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_vector_mul(sp_vector * a, const sp_vector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] *= b->data[i];
  }
}

/*! This function mutiplies the elements of Complex vector a with the elements of Complex vector b, a'_i = a_i * b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_cvector_mul(sp_cvector * a, const sp_cvector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] *= b->data[i];
  }
}

/*! This function divides the elements of vector a with the elements of vector b, a'_i = a_i / b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_vector_div(sp_vector * a, const sp_vector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] /= b->data[i];
  }
}

/*! This function divides the elements of the Complex vector a with the elements of the Complex vector b, a'_i = a_i / b_i. 
 *
 * The two vectors must have the same length.
 */
static inline void sp_cvector_div(sp_cvector * a, const sp_cvector * b){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] /= b->data[i];
  }
}


/*! This function multiplies the elements of vector a by the constant factor x, a'_i = x a_i.
 *
 */
static inline void sp_vector_scale(sp_vector * a, const real x){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] *= x;
  }
}

/*! This function multiplies the elements of a Complex vector a by the constant factor x, a'_i = x a_i.
 *
 */
static inline void sp_cvector_scale(sp_cvector * a, const Complex x){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] *= x;
  }
}


/*! This function adds the constant value x to the elements of the vector a, a'_i = a_i + x.
 *
 */
static inline void sp_vector_add_constant(sp_vector * a, const real x){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] += x;
  }
}

/*! This function adds the constant value x to the elements of the Complex vector a, a'_i = a_i + x.
 *
 */
static inline void sp_cvector_add_constant(sp_cvector * a, const Complex x){
  int i;
  for(i = 0;i<a->size;i++){
    a->data[i] += x;
  }
}


/*! This function calculates the dot product of a and b.
  *
  * The two vectors must have the same length.
  */
static inline real sp_vector_dot_prod(sp_vector * a, const sp_vector * b){
  int i;
  real ret = 0;
  for(i = 0;i<a->size;i++){
    ret += a->data[i]*b->data[i];
  }
  return ret;
}

/*! This function calculates the dot product of a and b.
  *
  * The two vectors must have the same length.
  */
static inline real sp_cvector_dot_prod(sp_cvector * a, const sp_cvector * b){
  int i;
  real ret = 0;
  for(i = 0;i<a->size;i++){
    ret += a->data[i]*b->data[i];
  }
  return ret;
}


/*! This function calculates the outer product of vector a and b.
  *
  */
static inline sp_matrix * sp_vector_outer_prod(sp_vector * a, const sp_vector * b){
  int i,j;
  sp_matrix * ret = sp_matrix_alloc(a->size,b->size);
  for(i = 0;i<a->size;i++){
    for(j = 0;j<b->size;j++){
      sp_matrix_set(ret,i,j,a->data[i]*b->data[j]);
    }
  }
  return ret;
}


/*! This function calculates the norm of the vector a.
  *
  */
static inline real sp_vector_norm(sp_vector * a){
  int i;
  real ret = 0;
  for(i = 0;i<a->size;i++){
    ret += a->data[i]*a->data[i];
  }
  return sqrt(ret);
}

/*! This function calculates the norm of the vector a.
  *
  */
static inline real sp_cvector_norm(sp_cvector * a){
  int i;
  real ret = 0;
  for(i = 0;i<a->size;i++){
    ret += a->data[i]*a->data[i];
  }
  return sqrt(ret);
}


/*! This function copies the elements of the vector src into the vector dest. 
  *
  * The two vectors must have the same length.
  */
static inline void sp_vector_memcpy(sp_vector * dest, const sp_vector * src){
  int i;
  if(src->size < 1024){
    for(i = 0;i<src->size;i++){
      dest->data[i] = src->data[i];
    }
  }else{
    memcpy(dest->data,src->data,sizeof(real)*src->size);
  }

}

/*! This function copies the elements of the Complex vector src into the Complex vector dest. 
  *
  * The two vectors must have the same length.
  */
static inline void sp_cvector_memcpy(sp_cvector * dest, const sp_cvector * src){
  int i;
  if(src->size < 1024){
    for(i = 0;i<src->size;i++){
      dest->data[i] = src->data[i];
    }
  }else{
    memcpy(dest->data,src->data,sizeof(real)*src->size);
  }
}






/*! This function returns the number of cells in m, that is, rows*cols 
 *
 */
static inline int sp_matrix_size (const sp_matrix * m){
  return m->rows*m->cols;
}


/*! This function returns the number of cells in m, that is, rows*cols 
 *
 */
static inline int sp_imatrix_size (const sp_imatrix * m){
  return m->rows*m->cols;
}

/*! This function returns the number of cells in m, that is, rows*cols 
 *
 */
static inline int sp_cmatrix_size (const sp_cmatrix * m){
  return m->rows*m->cols;
}


/*! This function returns the number of rows in m
 *
 */
static inline int sp_matrix_rows (const sp_matrix * m){
  return m->rows;
}

/*! This function returns the number of rows in m
 *
 */
static inline int sp_imatrix_rows (const sp_imatrix * m){
  return m->rows;
}

/*! This function returns the number of rows in m
 *
 */
static inline int sp_cmatrix_rows (const sp_cmatrix * m){
  return m->rows;
}


/*! This function returns the number of colums in m
 *
 */
static inline int sp_matrix_cols (const sp_matrix * m){
  return m->cols;
}

/*! This function returns the number of colums in m
 *
 */
static inline int sp_imatrix_cols (const sp_imatrix * m){
  return m->cols;
}

/*! This function returns the number of colums in m
 *
 */
static inline int sp_cmatrix_cols (const sp_cmatrix * m){
  return m->cols;
}


/*! This function sets the diagonal elements of m to 1 and the rest to 0
 *
 */
static inline void sp_matrix_set_identity(sp_matrix * m){
  int i;
  memset(m->data,0,sizeof(real)*m->rows*m->cols);
  for(i = 0;i<m->rows && i<m->cols;i++){
    sp_matrix_set(m,i,i,1);
  }
}

/*! This function sets the diagonal elements of m to 1 and the rest to 0
 *
 */
static inline void sp_imatrix_set_identity(sp_imatrix * m){
  int i;
  memset(m->data,0,sizeof(int)*m->rows*m->cols);
  for(i = 0;i<m->rows && i<m->cols;i++){
    sp_imatrix_set(m,i,i,1);
  }
}

/*! This function sets the diagonal elements of m to 1 and the rest to 0
 *
 */
static inline void sp_cmatrix_set_identity(sp_cmatrix * m){
  int i;
  memset(m->data,0,sizeof(Complex)*m->rows*m->cols);
  for(i = 0;i<m->rows && i<m->cols;i++){
    sp_cmatrix_set(m,i,i,1);
  }
}




/*! This function adds the elements of matrix b to the elements of matrix a, a'_ij = a_ij + b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_matrix_add(sp_matrix * a, const sp_matrix * b){
  int i;
  for(i = 0;i<sp_matrix_size(b);i++){
    a->data[i] += b->data[i];
  }
}

/*! This function adds the elements of integer matrix b to the elements of integer matrix a, a'_ij = a_ij + b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_imatrix_add(sp_imatrix * a, const sp_imatrix * b){
  int i;
  for(i = 0;i<sp_imatrix_size(b);i++){
    a->data[i] += b->data[i];
  }
}

/*! This function adds the elements of Complex matrix b scaled by x to the elements of Complex matrix a
 *  a'_ij = a_ij + b_ij * x. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_cmatrix_add(sp_cmatrix * a, const sp_cmatrix * b, Complex * x){
  int i;
  if(x && *x != 1){
    for(i = 0;i<sp_cmatrix_size(b);i++){
      a->data[i] += b->data[i]*(*x);
    }
  }else{
    for(i = 0;i<sp_cmatrix_size(b);i++){
      a->data[i] += b->data[i];
    }
  }
}

/*! This function subtracts the elements of matrix b to the elements of matrix a, a'_ij = a_ij - b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_matrix_sub(sp_matrix * a, const sp_matrix * b){
  int i;
  for(i = 0;i<sp_matrix_size(b);i++){
    a->data[i] -= b->data[i];
  }
}


/*! This function subtracts the elements of integer matrix b to the elements of integer matrix a, a'_ij = a_ij - b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_imatrix_sub(sp_imatrix * a, const sp_imatrix * b){
  int i;
  for(i = 0;i<sp_imatrix_size(b);i++){
    a->data[i] -= b->data[i];
  }
}

/*! This function subtracts the elements of Complex matrix b to the elements of Complex matrix a, a'_ij = a_ij - b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_cmatrix_sub(sp_cmatrix * a, const sp_cmatrix * b){
  int i;
  for(i = 0;i<sp_cmatrix_size(b);i++){
    a->data[i] -= b->data[i];
  }
}

/*! This function mutiplies the elements of matrix a with the elements of matrix b, a'_ij = a_ij * b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_matrix_mul_elements(sp_matrix * a, const sp_matrix * b){
  int i;
  for(i = 0;i<sp_matrix_size(b);i++){
    a->data[i] *= b->data[i];
  }
}

/*! This function mutiplies the elements of integer matrix a with the elements of integer matrix b, a'_ij = a_ij * b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_imatrix_mul_elements(sp_imatrix * a, const sp_imatrix * b){
  int i;
  for(i = 0;i<sp_imatrix_size(b);i++){
    a->data[i] *= b->data[i];
  }
}

/*! This function mutiplies the elements of Complex matrix a with the elements of Complex matrix b, a'_ij = a_ij * b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_cmatrix_mul_elements(sp_cmatrix * a, const sp_cmatrix * b){
  int i;
  for(i = 0;i<sp_cmatrix_size(b);i++){
    a->data[i] *= b->data[i];
  }
}


/*! This function divides the elements of matrix a with the elements of matrix b, a'_ij = a_ij / b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_matrix_div_elements(sp_matrix * a, const sp_matrix * b){
  int i;
  for(i = 0;i<sp_matrix_size(b);i++){
    a->data[i] /= b->data[i];
  }
}

/*! This function divides the elements of integer matrix a with the elements of integer matrix b, a'_ij = a_ij / b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_imatrix_div_elements(sp_imatrix * a, const sp_imatrix * b){
  int i;
  for(i = 0;i<sp_imatrix_size(b);i++){
    a->data[i] /= b->data[i];
  }
}

/*! This function divides the elements of Complex matrix a with the elements of Complex matrix b, a'_ij = a_ij / b_ij. 
 *
 * The two matrices must have the same dimensions.
 */
static inline void sp_cmatrix_div_elements(sp_cmatrix * a, const sp_cmatrix * b){
  int i;
  for(i = 0;i<sp_cmatrix_size(b);i++){
    a->data[i] /= b->data[i];
  }
}


/*! This function multiplies the elements of the matrix a by the constant factor x, a'_ij = x a_ij.
 *
 */
static inline void sp_matrix_scale(sp_matrix * a, const real x){
  int i;
  for(i = 0;i<sp_matrix_size(a);i++){
    a->data[i] *= x;
  }
}

/*! This function multiplies the elements of the integer matrix a by the constant factor x, a'_ij = x a_ij.
 *
 */
static inline void sp_imatrix_scale(sp_imatrix * a, const real x){
  int i;
  for(i = 0;i<sp_imatrix_size(a);i++){
    a->data[i] *= x;
  }
}


/*! This function multiplies the elements of the Complex matrix a by the constant factor x, a'_ij = x a_ij.
 *
 */
static inline void sp_cmatrix_scale(sp_cmatrix * a, const Complex x){
  int i;
  for(i = 0;i<sp_cmatrix_size(a);i++){
    a->data[i] *= x;
  }
}


/*! This function adds the constant value x to the elements of the matrix a, a'_ij = a_ij + x.
 *
 */
static inline void sp_matrix_add_constant(sp_matrix * a, const real x){
  int i;
  for(i = 0;i<sp_matrix_size(a);i++){
    a->data[i] += x;
  }
}

/*! This function adds the constant value x to the elements of the integer matrix a, a'_ij = a_ij + x.
 *
 */
static inline void sp_imatrix_add_constant(sp_imatrix * a, const int x){
  int i;
  for(i = 0;i<sp_imatrix_size(a);i++){
    a->data[i] += x;
  }
}


/*! This function adds the constant value x to the elements of the Complex matrix a, a'_ij = a_ij + x.
 *
 */
static inline void sp_cmatrix_add_constant(sp_cmatrix * a, const Complex x){
  int i;
  for(i = 0;i<sp_cmatrix_size(a);i++){
    a->data[i] += x;
  }
}

/*! This function transposes matrix a.
 *
 */
static inline void sp_matrix_transpose(sp_matrix * a){
  int i,j;
  /* exchange dimensions */
  sp_matrix * tmp = sp_matrix_alloc(a->cols,a->rows);
  for(i = 0;i<a->rows;i++){
    for(j = 0;j<a->cols;j++){
      sp_matrix_set(tmp,j,i,sp_matrix_get(a,i,j));
    }
  }
  /* copy from tmp the useful things and discard original array */
  a->cols = tmp->cols;
  a->rows = tmp->rows;
  free(a->data);
  a->data = tmp->data;
  free(tmp);
}


/*! This function transposes matrix a.
 *
 */
static inline void sp_imatrix_transpose(sp_imatrix * a){
  int i,j;
  /* exchange dimensions */
  sp_imatrix * tmp = sp_imatrix_alloc(a->cols,a->rows);
  for(i = 0;i<a->rows;i++){
    for(j = 0;j<a->cols;j++){
      sp_imatrix_set(tmp,j,i,sp_imatrix_get(a,i,j));
    }
  }
  /* copy from tmp the useful things and discard original array */
  a->cols = tmp->cols;
  a->rows = tmp->rows;
  free(a->data);
  a->data = tmp->data;
  free(tmp);
}


/*! This function transposes Complex matrix a.
 *
 * The Complex conjugate of the cells is not calculated
 */
static inline void sp_cmatrix_transpose(sp_cmatrix * a){
  int i,j;
  /* exchange dimensions */
  sp_cmatrix * tmp = sp_cmatrix_alloc(a->cols,a->rows);
  for(i = 0;i<a->rows;i++){
    for(j = 0;j<a->cols;j++){
      sp_cmatrix_set(tmp,j,i,sp_cmatrix_get(a,i,j));
    }
  }
  /* copy from tmp the useful things and discard original array */
  a->cols = tmp->cols;
  a->rows = tmp->rows;
  free(a->data);
  a->data = tmp->data;
  free(tmp);
}


/*! This function returns the product of matrix m with vector v.
 *
 *  The size of v must be the same as the number of cols in m.
 */
static inline sp_vector * sp_matrix_vector_prod(const sp_matrix * m, const sp_vector * v){
  int i,j;
  sp_vector * ret = sp_vector_alloc(m->rows);
  for(i = 0;i<m->rows;i++){
    for(j = 0;j<m->cols;j++){
      ret->data[i] += sp_matrix_get(m,i,j)*v->data[j];
    }
  }
  return ret;
}

/*! This function returns the product of Complex matrix m with Complex vector v.
 *
 *  The size of v must be the same as the number of cols in m.
 */
static inline sp_cvector * sp_cmatrix_cvector_prod(const sp_cmatrix * m, const sp_cvector * v){
  int i,j;
  sp_cvector * ret = sp_cvector_alloc(m->rows);
  for(i = 0;i<m->rows;i++){
    for(j = 0;j<m->cols;j++){
      ret->data[i] += sp_cmatrix_get(m,i,j)*v->data[j];
    }
  }
  return ret;
}


/*! This function returns the product of matrix a with matrix b.
 *
 *  The size of a must be the same as the size of the transpose of b.
 */
static inline sp_matrix * sp_matrix_mul(const sp_matrix * a, const sp_matrix * b){
  int i,j,k;
  real tmp;
  sp_matrix * ret = sp_matrix_alloc(a->rows,b->cols);
  for(i = 0;i<a->rows;i++){
    for(j = 0;j<b->cols;j++){
      tmp = 0;
      for(k = 0;k<a->cols;k++){
	tmp += sp_matrix_get(a,i,k)*sp_matrix_get(b,k,j);
      }
      sp_matrix_set(ret,i,j,tmp);
    }
  }
  return ret;
}

/*! This function returns the product of Complex matrix a with Complex matrix b.
 *
 *  The size of a must be the same as the size of the transpose of b.
 */
static inline sp_cmatrix * sp_cmatrix_mul(const sp_cmatrix * a, const sp_cmatrix * b){
  int i,j,k;
  real tmp;
  sp_cmatrix * ret = sp_cmatrix_alloc(a->rows,b->cols);
  for(i = 0;i<a->rows;i++){
    for(j = 0;j<b->cols;j++){
      tmp = 0;
      for(k = 0;k<a->cols;k++){
	tmp += sp_cmatrix_get(a,i,k)*sp_cmatrix_get(b,k,j);
      }
      sp_cmatrix_set(ret,i,j,tmp);
    }
  }
  return ret;
}

/*! This function scales all elements of row n of matrix m by x.
 *
 */
static inline void sp_matrix_scale_row(sp_matrix * m, int n, real x){
  int i;
  for(i = 0;i<sp_matrix_cols(m);i++){
    sp_matrix_set(m,n,i,sp_matrix_get(m,n,i)*x);
  }
}

/*! This function scales all elements of row n of Complex matrix m by x.
 *
 */
static inline void sp_cmatrix_scale_row(sp_cmatrix * m, int n, Complex x){
  int i;
  for(i = 0;i<sp_cmatrix_cols(m);i++){
    sp_cmatrix_set(m,n,i,sp_cmatrix_get(m,n,i)*x);
  }
}

/*! This function add the elements of row from, multiplied by factor, to the elements of row to, of matrix m.
 *
 */
static inline void sp_matrix_row_add_row(sp_matrix * m, int from, int to, real factor){
  int i;
  for(i = 0;i<sp_matrix_cols(m);i++){
    sp_matrix_set(m,to,i,sp_matrix_get(m,from,i)*factor+sp_matrix_get(m,to,i));
  }
}

/*! This function add the elements of row from, multiplied by factor, to the elements of row to, of Complex matrix m.
 *
 */
static inline void sp_cmatrix_row_add_row(sp_cmatrix * m, int from, int to, Complex factor){
  int i;
  for(i = 0;i<sp_cmatrix_cols(m);i++){
    sp_cmatrix_set(m,to,i,sp_cmatrix_get(m,from,i)*factor+sp_cmatrix_get(m,to,i));
  }
}

/*! This functions returns the inverse of matrix a.
 *
 */
spimage_EXPORT void sp_matrix_invert(sp_matrix * a);

/*! This functions tries to print the matrix in a human readable way
 */
spimage_EXPORT void sp_matrix_print(sp_matrix * a, FILE * fp);


/*! This functions returns the inverse of Complex matrix a.
 *
 */
spimage_EXPORT void sp_cmatrix_invert(sp_cmatrix * a);

/*! This functions tries to print the Complex matrix in a human readable way
 */
spimage_EXPORT void sp_cmatrix_print(sp_cmatrix * a, FILE * fp);


/*! This function returns a cvector numerically similar to v
 *
 * The elements of v are copied to the real part of the result
 */
static inline sp_cvector * sp_vector_to_cvector(const sp_vector * v){
  int i;
  int size = sp_vector_size(v);
  sp_cvector * ret = sp_cvector_alloc(size);
  for(i = 0;i<size;i++){
    ret->data[i] = v->data[i];
  }
  return ret;
}

/*! This function returns a cmatrix numerically similar to m
 *
 * The elements of m are copied to the real part of the result
 */
static inline sp_cmatrix * sp_matrix_to_cmatrix(const sp_matrix * m){
  int i,j;
  int rows = sp_matrix_rows(m);
  int cols = sp_matrix_cols(m);
  sp_cmatrix * ret = sp_cmatrix_alloc(rows,cols);
  for(i = 0;i<rows;i++){
    for(j = 0;j<cols;j++){
      sp_cmatrix_set(ret,i,j,sp_matrix_get(m,i,j));
    }
  }
  return ret;
}



/*! This function returns the index of a given row and column combination
 *
 */
static inline int sp_matrix_get_index(const sp_matrix * m, const int row, const int col){
  return col*m->rows+row;
}


/*! This function returns the index of a given row and column combination
 *
 */
static inline int sp_imatrix_get_index(const sp_imatrix * m, const int row, const int col){
  return col*m->rows+row;
}

/*! This function returns the index of a given row and column combination
 *
 */
static inline int sp_cmatrix_get_index(const sp_cmatrix * m, const int row, const int col){
  return col*m->rows+row;
}


/*! This function changes m to it's complex conjugate
 *
 */
static inline void sp_cmatrix_conj(sp_cmatrix * m){
  int i;
  for(i = 0;i<sp_cmatrix_size(m);i++){
    m->data[i] = conjr(m->data[i]);
  }
}

/*! Returns the cabs value of the element with the smallest cabs
 *
 */
static inline real sp_cmatrix_min(const sp_cmatrix * m, int * index){
  real min = cabsr(m->data[0]);
  int i,ii;
  for(i = 1;i<sp_cmatrix_size(m);i++){
    if(cabsr(m->data[i]) < min){
      min = cabsr(m->data[i]);
      ii = i;
    }
  }
  if(index){
    *index = ii;
  }
  return min;
}

/*! Returns the cabs value of the element with the biggest cabs
 *
 */
static inline real sp_cmatrix_max(const sp_cmatrix * m, int * index){
  real max = cabsr(m->data[0]);
  int i;
  int i_max = 0;
  for(i = 1;i<sp_cmatrix_size(m);i++){
    if(cabsr(m->data[i]) > max){
      max = cabsr(m->data[i]);
      i_max = i;
    }
  }
  if(index){
    *index = i_max;
  }
  return max;
}


/*! Returns the interpolated value of m at the floating point row frow and column fcol
 *
 */
static inline Complex sp_cmatrix_interp(const sp_cmatrix * m, real frow, real fcol){
  int x = fcol;
  int y = frow;
  real u = fcol-x;
  real v = frow-y;
  Complex res = 0;
  if(x >= sp_cmatrix_cols(m)-1){
    x = sp_cmatrix_cols(m)-2;
    u = 1;
  }
  if(y >= sp_cmatrix_rows(m)-1){
    y = sp_cmatrix_rows(m)-2;
    v = 1;
  }
  res = sp_cmatrix_get(m,y,x)*(1-u)*(1-v)+
    sp_cmatrix_get(m,y,x+1)*(u)*(1-v)+
    sp_cmatrix_get(m,y+1,x)*(1-u)*(v)+
    sp_cmatrix_get(m,y+1,x+1)*(u)*(v);
  return res;
}

/*! Returns the interpolated value of m at the floating point row frow and column fcol
 *
 */
static inline real sp_matrix_interp(const sp_matrix * m, real frow, real fcol){
  int x = fcol;
  int y = frow;
  real u = fcol-x;
  real v = frow-y;
  real res = 0;
  if(x >= sp_matrix_cols(m)-1){
    x = sp_matrix_cols(m)-2;
    u = 1;
  }
  if(y >= sp_matrix_rows(m)-1){
    y = sp_matrix_rows(m)-2;
    v = 1;
  }
  res = sp_matrix_get(m,y,x)*(1-u)*(1-v)+
    sp_matrix_get(m,y,x+1)*(u)*(1-v)+
    sp_matrix_get(m,y+1,x)*(1-u)*(v)+
    sp_matrix_get(m,y+1,x+1)*(u)*(v);
  return res;
}


/*! Returns the interpolated value of m at the floating point row frow and column fcol
 *
 */
static inline int sp_imatrix_interp(const sp_imatrix * m, real frow, real fcol){
  int x = fcol;
  int y = frow;
  real u = fcol-x;
  real v = frow-y;
  int res = 0;
  if(x >= sp_imatrix_cols(m)-1){
    x = sp_imatrix_cols(m)-2;
    u = 1;
  }
  if(y >= sp_imatrix_rows(m)-1){
    y = sp_imatrix_rows(m)-2;
    v = 1;
  }
  res = sp_imatrix_get(m,y,x)*(1-u)*(1-v)+
    sp_imatrix_get(m,y,x+1)*(u)*(1-v)+
    sp_imatrix_get(m,y+1,x)*(1-u)*(v)+
    sp_imatrix_get(m,y+1,x+1)*(u)*(v);
  return res;
}

/*! Resizes complex matrix m to the desired size. 
 *
 *  The content of the matrix will be destroyed.
 */
static inline void sp_cmatrix_realloc(sp_cmatrix * m, int row, int col){
  m->rows = row;
  m->cols = col;
  m->data = realloc(m->data,sizeof(Complex)*sp_cmatrix_size(m));
}

/*! Resizes integer matrix m to the desired size. 
 *
 *  The content of the matrix will be destroyed.
 */
static inline void sp_imatrix_realloc(sp_imatrix * m, int row, int col){
  m->rows = row;
  m->cols = col;
  m->data = realloc(m->data,sizeof(int)*sp_imatrix_size(m));
}

/*! Resizes matrix m to the desired size. 
 *
 *  The content of the matrix will be destroyed.
 */
static inline void sp_matrix_realloc(sp_matrix * m, int row, int col){
  m->rows = row;
  m->cols = col;
  m->data = realloc(m->data,sizeof(real)*sp_matrix_size(m));
}


/*! This function returns the index of a given row and column combination
 *
 */
static inline void sp_cmatrix_get_row_col(const sp_cmatrix * m, int index, int * row, int * col){
  *row = index%m->rows;
  *col = index/m->rows;
}


/*! This function sets the real part to the cabs of each element and the complex part to 0
 *
 */
static inline void sp_cmatrix_to_real(const sp_cmatrix * m){
  int i;
  for(i = 0;i<sp_cmatrix_size(m);i++){
    m->data[i] = cabsr(m->data[i]);
  }
}


/*! This function returns the Froebius inner product of complex matrix a and b
 *
 * The Froebius inner product is defined as the sum of a element by element multiplication
 * of the matrix elements. It's the basis for the Froebius norm.
 * Both matrices must obviously have the same dimensions.
 */

static inline Complex sp_cmatrix_froebius_prod(const sp_cmatrix * a, const sp_cmatrix * b){
  Complex ret = 0; 
  int i;
  for(i = 0;i<sp_cmatrix_size(a);i++){
    ret += a->data[i]*conjr(b->data[i]);
  }
  return ret;
}

#endif
