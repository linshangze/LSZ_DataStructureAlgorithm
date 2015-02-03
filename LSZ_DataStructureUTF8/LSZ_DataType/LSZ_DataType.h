/********************************************************************
 *File Name: LSZ_DataType.h
 *Author: Linshangze//林上泽
 *Mail: linshangze163@163.com
 *Created Time: 2013-08-28
 *Updated Time: 2015-01-10
 *******************************************************************/

/********************************************************************
 *header file of LSZ_DataType
 *LSZ_ElementType头文件
 *******************************************************************/

#ifndef _LSZ_DATATYPE_H_
#define _LSZ_DATATYPE_H_

//////////////////////////////////////////////////////////////////////
//带有长度属性的数据类型定义
//////////////////////////////////////////////////////////////////////

/**
 * the atom type
 * 原子类型
 */
typedef unsigned char LSZ_AT;

/**
 * the type of length
 * 长度类型
 */
typedef unsigned int LSZ_LT;

/**
 * the molecule type
 * 分子类型
 */
typedef struct LSZ_MType{
	LSZ_AT* data; //存储起始地址。
	LSZ_LT len; //存储空间长度，字节算。
}LSZ_MT;

/////////////////////////////////////////////////////////////////////
//macros
//宏定义
/////////////////////////////////////////////////////////////////////

//置全位零
#define _LSZ_FUN_AT_SET0(e) ((e) = 0)
//判全位零
#define _LSZ_FUN_AT_IS0(e) (!((e) ^ 0))
//置非零
#define _LSZ_FUN_AT_SET1(e) ((e) = ~0)
//判非零
#define _LSZ_FUN_AT_ISN0(e) ((e) ^ 0)
//设值
#define _LSZ_FUN_AT_SET(e1, e2) ((e1) = (e2))
//判等
#define _LSZ_FUN_AT_EQ(e1, e2) ((e1) == (e2))
//判大于
#define _LSZ_FUN_AT_GT(e1, e2) ((e1) > (e2))
//判小于
#define _LSZ_FUN_AT_LT(e1, e2) ((e1) < (e2))
//交换
//0=1^=1,1=1^=0,1=0^=1;
//1=1^=0,1=0^=1,0=1^=1;
//1=0^=1,0=1^=1,1=1^=0;
//0=0^=0,0=0^=0,0=0^=0;
//修正异或交换不支持同一个变量交换。
#define _LSZ_FUN_AT_SWAP(e1, e2) \
	(((e1) ^ (e2)) && ((e1) ^= (e2), (e2) ^= (e1), (e1) ^= (e2), 1))

/////////////////////////////////////////////////////////////////////
//declaration of functions
//函数声明
/////////////////////////////////////////////////////////////////////

/**
 * 初始化原子类型，值全位置零。
 */
#define LSZ_AT_init(e) \
	_LSZ_FUN_AT_SET0(e)

/**
 * 销毁原子类型，值置非零。
 */
#define LSZ_AT_dest(e) \
	_LSZ_FUN_AT_SET1(e)

/**
 * 计算原子类型，存储大小，以字节计算。
 */
#define LSZ_AT_size(e) \
	(sizeof(e))

/**
 * 读取原子类型值。
 */
#define LSZ_AT_rd(dst, src) \
	_LSZ_FUN_AT_SET(dst, src)

/**
 * 修改原子类型值。
 */
#define LSZ_AT_wt(dst, src) \
	_LSZ_FUN_AT_SET(dst, src)

/**
 * 赋值一LSZ_AT类型。
 */
#define LSZ_AT_sign(dst, src) \
	_LSZ_FUN_AT_SET(dst, src)

/**
 * 交换两原子类型值。
 */
#define LSZ_AT_swap(e1, e2) \
	_LSZ_FUN_AT_SWAP(e1, e2)

/**
 * 两原子类型值大于比较。
 */
#define LSZ_AT_gt(e1, e2) \
	_LSZ_FUN_AT_GT(e1, e2)
/**
 * 两原子类型值等于比较。
 */
#define LSZ_AT_eq(e1, e2) \
	_LSZ_FUN_AT_EQ(e1, e2)
/**
 * 两原子类型值小于比较。
 */
#define LSZ_AT_lt(e1, e2) \
	_LSZ_FUN_AT_LT(e1, e2)

/**
 * to initialize a LSZ_MT.
 * 初始化一LSZ_MT类型。
 */
extern int LSZ_MT_init(LSZ_MT* e);

/**
 * to destroy a LSZ_MT.
 * 销毁一LSZ_MT类型。
 */
extern int LSZ_MT_dest(LSZ_MT* e);

/**
 * calculate the size of LSZ_MT.
 * 计算一LSZ_MT类型的元素空间大小。
 */
#define LSZ_MT_size(e) \
	((unsigned long)((e)->len))

/**
 * read the value of LSZ_MT.
 * 读取一LSZ_MT类型的值。
 */
extern int LSZ_MT_rd(LSZ_AT* dst,
				LSZ_MT* src);
#ifndef _LSZ_DATATYPE_C_
#define LSZ_MT_rd(dst, src) \
	LSZ_MT_rd((LSZ_AT*)(dst), src)
#endif

/**
 * modify the value of LSZ_MT.
 * 修改一LSZ_MT类型的值。
 * 不支持字符串常量类型。
 */
extern int LSZ_MT_wt_(LSZ_MT* dst,
				LSZ_AT* src,
				LSZ_LT len);
#ifndef _LSZ_DATATYPE_C_
#define LSZ_MT_wt(dst, src) \
	LSZ_MT_wt_(dst, (LSZ_AT*)(src), sizeof(*(src)))
#endif

/**
 * 赋值一LSZ_MT类型。
 */
extern int LSZ_MT_sign(LSZ_MT* dst,
				LSZ_MT* src);
/**
 * to fill the data saved in 'e' with zero each bit.
 * return the length of data in byte if successfully.
 * 将e存储的数据按位置零。
 * 成功返回数据的以字节算的长度。
 */
extern int LSZ_MT_wt0(LSZ_MT* e);

/**
 * to compare two LSZ_MT according CmpFun,
 * CmpFun will decide the value returned.
 * 比较两个LSZ_MT类型，通过CmpFun函数判断得到返回值。
 */
#define LSZ_MT_cmp(e1, e2, CmpFun) \
	(CmpFun(e1, e2))

/**
 * to compare two LSZ_MT according CmpFun,
 * CmpFun will decide the value returned.
 * 0 will be return if they are equal.
 * 比较两个LSZ_MT类型，通过CmpFun函数判断得到返回值。
 * 相同返回0，否则返回非零。
 */
extern int LSZ_MT_eq(LSZ_MT* e1,
				LSZ_MT* e2);

/**
 * to swap two data saved in 'e1' and 'e2'.
 * return the length of data swapped in byte if successfully.
 * 交换e1和e2中存储的数据。。
 * 成功返回交换的数据的以字节算的长度。
 */
extern int LSZ_MT_swap(LSZ_MT* e1,
				LSZ_MT* e2);

//////////////////////////////////////////////////////////////////////
//用地址标识的数据类型定义
//////////////////////////////////////////////////////////////////////

/**
 */
typedef unsigned char LSZ_LocT;

// the end of file
#endif
