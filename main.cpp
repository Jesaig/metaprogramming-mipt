#include <gtest/gtest.h>
#include "TypeList.hpp"
#include <iostream>


/***************LENGTH TESTS***************/

TEST (LengthTest, EmptyList) {

    using EmptyList = TypeList<>;
    ASSERT_EQ(0, Length<EmptyList>::value);

}

TEST (LengthTest, IntList) {

	using IntList = TypeList<int>;
    ASSERT_EQ(1, Length<IntList>::value);

}

TEST (LengthTest, IntDoubleList) {

	using IntFloatList = TypeList<int, float>;
    ASSERT_EQ(2, Length<IntFloatList>::value);

}

TEST (LengthTest, MyTypesList) {

	using MyTypes = TypeList<int, float, double>;
    ASSERT_EQ(3, Length<MyTypes>::value);

}


/***************TYPE AT TESTS***************/

TEST (AtTest, MyTypesList) {

	using MyTypes = TypeList<int, float, double>;

	ASSERT_EQ(typeid(int), typeid(TypeAt<MyTypes, 0>::Result));
	ASSERT_EQ(typeid(float), typeid(TypeAt<MyTypes, 1>::Result));
	ASSERT_EQ(typeid(double), typeid(TypeAt<MyTypes, 2>::Result));

}


/***************INDEX OF TESTS***************/

TEST (IndexOfTest, EmptyList) {

	using EmptyList = TypeList<>;

	int result = IndexOf<EmptyList, char>::value;
	ASSERT_EQ(-1, result);

}

TEST (IndexOfTest, IntList) {

	using IntList = TypeList<int>;

	int result = IndexOf<IntList, int>::value;
	ASSERT_EQ(0, result);

}

TEST (IndexOfTest, IntDoubleList) {

	using IntDoubleList = TypeList<int, double>;

	int result = IndexOf<IntDoubleList, int>::value;
	ASSERT_EQ(0, result);

	result = IndexOf<IntDoubleList, double>::value;
	ASSERT_EQ(1, result);

}


/***************APPEND TESTS***************/

TEST (AppendTest, EmptyList) {

	using EmptyList = TypeList<>;
	using Result = Append<EmptyList, NullType>::Result;

	ASSERT_EQ(typeid(EmptyList), typeid(Result));

}

TEST (AppendTest, IntList) {

	using EmptyList = TypeList<>;
	using IntList = TypeList<int>;
	using Result = Append<EmptyList, int>::Result;

	ASSERT_EQ(typeid(IntList), typeid(Result));

}

TEST (AppendTest, IntDoubeList) {

	using EmptyList = TypeList<>;
	using IntDoubeList = TypeList<int, double>;
	using Result = Append<EmptyList, IntDoubeList>::Result;

	ASSERT_EQ(typeid(IntDoubeList), typeid(Result));

}

TEST (AppendTest, MyTypesList) {

	using IntDoubleList = TypeList<int, double>;
	using CharList = TypeList<char>;
	using MyTypesList = TypeList<int, TypeList<double, TypeList<char> > >;
	using Result = Append<IntDoubleList, CharList>::Result;

	ASSERT_EQ(typeid(MyTypesList), typeid(Result));

}


/***************ERASE TESTS***************/

TEST (EraseTest, EmptyList) {

	using EmptyList = TypeList<>;
	using Result = Erase<EmptyList, int>::Result;

	ASSERT_EQ(typeid(EmptyList), typeid(Result));

}

TEST (EraseTest, IntList) {

	using IntList = TypeList<int>;
	using Result = Erase<IntList, int>::Result;

	ASSERT_EQ(typeid(NullType), typeid(Result));

}

TEST (EraseTest, IntDoubleList) {

	using IntDoubleList = TypeList<int, double>;

	using Result = Erase<IntDoubleList, int>::Result;
	ASSERT_EQ(typeid(TypeList<double>), typeid(Result));

	using NextResult = Erase<Result, double>::Result;
	ASSERT_EQ(typeid(NullType), typeid(NextResult));

}

TEST (EraseTest, ToughTest) {

	using EmptyList = TypeList<>;
	unsigned int length = Length<EmptyList>::value;
	ASSERT_EQ(0, length);

	using IntList = Append<EmptyList, int>::Result;
	length = Length<IntList>::value;
	ASSERT_EQ(1, length);

	using IntDoubleList = Append<IntList, double>::Result;
	length = Length<IntDoubleList>::value;
	ASSERT_EQ(2, length);

	ASSERT_EQ(typeid(int), typeid(TypeAt<IntDoubleList, 0>::Result));

	ASSERT_EQ(typeid(double), typeid(TypeAt<IntDoubleList, 1>::Result));

	using MyTypesList = Append<IntDoubleList, char>::Result;
	length = Length<MyTypesList>::value;
	ASSERT_EQ(3, length); 

	using MyTypesListWithString = Append<MyTypesList, std::string>::Result;
	length = Length<MyTypesListWithString>::value;
	ASSERT_EQ(4, length);

	ASSERT_EQ(2, (IndexOf<MyTypesListWithString, char>::value));

	ASSERT_EQ(3, (IndexOf<MyTypesListWithString, std::string>::value));

	using First = Erase<MyTypesListWithString, int>::Result;
	ASSERT_EQ(typeid(TypeList<double, TypeList<char, TypeList<std::string> > >),
			typeid(First));

	using Second = Erase<MyTypesListWithString, std::string>::Result;
	ASSERT_EQ(typeid(TypeList<int, TypeList<double, TypeList<char, NullType> > >),
		typeid(Second));

}


int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
