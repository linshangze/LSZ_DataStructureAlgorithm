/*********************************************************************
 * File Name: LSZ_Matrix.h
 * Author: linshangze
 * Mail: linshangze163@163.com 
 * Created Time: 2015-01-20-09:59:35 PM
 * Updated  Time: 2015-01-20-09:59:35 PM
 ********************************************************************/

/********************************************************************
 *header file of LSZ_DataType
 *LSZ_ElementType头文件
 *c语言提供一维和二维数组，所以在这里对数组操作扩展
 *******************************************************************/

#ifndef _LSZ_MATRIX_H_
#define _LSZ_MATRIX_H_

/////////////////////////////////////////////////////////////////////
//macro
//宏定义
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//definition of type
//数据类型定义
/////////////////////////////////////////////////////////////////////

//使用c语言的一维和二维数组

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * the memory space of symmetria matrix
 * 计算n阶的对称阵的一维存储大小
 */
#define LSZ_Matrix_symmSize(rank) \
	(((rank) * ((rank) + 1)) >> 1)

/**
 * 定位n阶的对称阵的元素存储下标。
 */
#define LSZ_Matrix_symmIndex(i, j) \
	((i) >= (j) ? \
	 (((i) * ((i) + 1)) >> 1) + (j): \
	 (((j) * ((j) + 1)) >> 1) + (i))

/**
 * the memory space of diagoal matrix
 * 计算n阶m条非零对角线的对角阵的一维存储大小
 * 利用完整矩阵元素个数减去0元个数，
 * 一缺点是乘法可能溢出。
 * 加两空间是因为对角阵不是每个元素都可以在一维中有唯一地址。
 * 一空间用于访问0元时编址，一空间为存错放在零元的非零数据编址。
 */
#define LSZ_Matrix_diagSize(rank, line) \
	((rank) * (rank) - \
	 (LSZ_Matrix_symmSize((rank) - ((line) >> 1) - 1) << 1))

/**
 * 定位n阶m条非零对角线的对角阵的元素存储下标
 *
 * n阶7条非零对角线矩阵中各对角线元素个数，左下到右上：
 *     .0. (n-3)  (n-2)  (n-1)  (n)  (n-1)  (n-2)  (n-3)  .0.
 * 累加：  (n-3) (2n-5) (3n-6)(4n-6) (5n-7) (6n-9) (7n-12)
 * i-j：     3      2     1      0     -1     -2     -3
 * 累加项可以看作由一等差项和一尾项合成
 * n的系数： (7 / 2) - (i - j) + 1
 * 当i >= j，每条对角线利用累加值和j下标顺序排放
 * 对称尾项为一等差数列和：-((7/2) + (i-j)) * ((7/2)-(i-j)+1) / 2
 * 当i < j，每条对角线利用累加值和i下标顺序排放，注意0下标。
 * 对称尾项为一等差数列和加前情况和：
 * 前一情况的和+(i-j)) * ((j-i)+1) / 2
 * 例如：
 * a00 a01 a02  0   0
 * a10 a11 a12 a13  0
 * a20 a21 a22 a23 a24
 *  0  a31 a32 a33 a34
 *  0   0  a42 a43 a44
 * 一维压缩后排序为：
 * a42 a31 a20 a43 a32 a21 a10 a44 a33 a22 a11 a00
 * a34 a23 a12 a01 a24 a13 a02
 * 算法很严重的缺点是表达复杂，多重括号，运算慢。
  */
#define LSZ_Matrix_diagIndex(rank, line, i, j) \
	((((i)-(j)>=((line)>>1)+1) || ((j)-(i)>=((line)>> 1)+1)) ? -1 : \
	LSZ_Matrix_diagIndex_(rank, line, i, j, ((line)>>1), (i)-(j)))
#define LSZ_Matrix_diagIndex_(rank, line, i, j, k, dst_ij) \
	(-1+((k)-(dst_ij)+1)*(rank) + \
	((i) >= (j) ? -((((k)+(dst_ij))*((k)-(dst_ij)+1))>>1) - (j): \
	-(((k)*((k)+1))>>1)+(((dst_ij)*((j)-(i)+1))>>1)-(i)))

//the end of file
#endif

