class NullType{};

template<typename T=NullType, typename ...U>
struct TypeList {

    using head = T;
    using tail = TypeList<U...>;

};

template<typename T>
struct TypeList<T> {

    using head = T;
    using tail = NullType;

};

template<typename Head>
struct TypeList<Head, TypeList<> > {

	using head = Head;
	using tail = NullType;

};

template<typename Head, typename OtherHead, typename ...OtherTail>
struct TypeList<Head, TypeList<OtherHead, OtherTail...> > {

	using head = Head;
	using tail = TypeList<OtherHead, OtherTail...>;

};


/***************LENGTH***************/

template<typename TypeList>
struct Length;

template<typename Head, typename ...Tail>
struct Length<TypeList<Head, Tail...> > {

    enum { value = Length<typename TypeList<Head, Tail...>::tail>::value + 1 };

};

template<>
struct Length<TypeList<>> {

    enum { value = 0 };

};

template<typename Head>
struct Length<TypeList<Head>> {

	enum { value = 1 };

};


/***************TYPE AT***************/

template<typename TypeList, unsigned int index>
struct TypeAt;

template<typename Head, typename ...Tail>
struct TypeAt<TypeList<Head, Tail...>, 0 > {

	using Result = Head;

};

template<typename Head, typename ...Tail, unsigned int index>
struct TypeAt<TypeList<Head, Tail...>, index> {

	using Result = typename TypeAt<typename TypeList<Head, Tail...>::tail, index - 1>::Result;

};


/***************INDEX OF***************/

template<typename TypeList, typename T>
struct IndexOf;

template<typename T>
struct IndexOf<TypeList<>, T> {

	enum { value = -1 };

};

template<typename ...Tail, typename T>
struct IndexOf<TypeList<T, Tail...>, T> {

	enum { value = 0 };

};

template<typename Head, typename ...Tail, typename T>
struct IndexOf<TypeList<Head, Tail...>, T> {

private:
	enum { temp = IndexOf<typename TypeList<Head, Tail...>::tail, T>::value };

public:
	enum { value = temp == -1 ? -1 : temp + 1 };

};


/***************APPEND***************/

template<typename TypeList, typename T>
struct Append;

template<>
struct Append<NullType, NullType> {

	using Result = NullType; 

};

template<typename T>
struct Append<NullType, T> {

	using Result = TypeList<T>;

};

template<typename Head, typename ...Tail>
struct Append<NullType, TypeList<Head, Tail...> > {

	using Result = TypeList<Head, Tail...>;

};

template<>
struct Append<TypeList<>, NullType> {

	using Result = TypeList<>; 

};

template<typename T>
struct Append<TypeList<>, T> {

	using Result = TypeList<T>; 

};

template<typename Head, typename ...Tail>
struct Append<TypeList<>, TypeList<Head, Tail...> > {

	using Result = TypeList<Head, Tail...>;

};

template<typename Head, typename ...Tail, typename T> 
struct Append<TypeList<Head, Tail...>, T> {
	
	using Result = TypeList<Head, 
		typename Append<typename TypeList<Head, Tail...>::tail, T>::Result>; 

};


/***************ERASE***************/

template<typename TypeList, typename T>
struct Erase;

template<typename T>
struct Erase<NullType, T> {

	using Result = NullType;

};

template<typename T>
struct Erase<TypeList<>, T> {

	using Result = TypeList<>;

};

template<typename ...Tail, typename T>
struct Erase<TypeList<T, Tail...>, T> {

	using Result = typename TypeList<T, Tail...>::tail;

};

template<typename Head, typename ...Tail, typename T>
struct Erase<TypeList<Head, Tail...>, T> {

	using Result = TypeList<Head, 
		typename Erase<typename TypeList<Head, Tail...>::tail, T>::Result>;

};