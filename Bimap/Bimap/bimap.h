#pragma once

template<typename Tkey, typename Tval>
class Bimap //final
{
public:
	std::size_t size() const;
	bool isEmpty() const;

	bool checkKey(const Tkey& key) const;
	bool checkVal(const Tval& val) const;

	bool insert(const Tkey& key, const Tval& val);
	bool emplace(Tkey&& key, Tval&& val);

	void keyErase(const Tkey& key);
	void valErase(const Tval& val);

	//std::pair<std::reference_wrapper<Tkey>, std::reference_wrapper<Tval>> keyGet(const Tkey& key) const;
	//std::pair<std::reference_wrapper<Tkey>, std::reference_wrapper<Tval>> valGet(const Tval& val) const;

	using RefPair = std::pair<std::reference_wrapper<const Tkey>, std::reference_wrapper<const Tval>>;

	RefPair keyGet(const Tkey& key) const;
	RefPair valGet(const Tval& val) const;

	Bimap() {

	}

	~Bimap() {

	}

};