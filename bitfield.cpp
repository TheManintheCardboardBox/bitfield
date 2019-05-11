#include "bitfield.hpp"

namespace lab {

	bitfield::bitfield(std::size_t len)
	{
		if (len < 0 || len > maxlen)
			throw std::length_error(LENGTH_ERROR);

		memlen = (bitlen = len) / (sizeof(std::size_t) * 8) + 1;
		pMem = new std::size_t[memlen]{ 0 };
	}

	bitfield::bitfield(const bitfield& other)
	{
		bitlen = other.bitlen;
		memlen = other.memlen;

		pMem = new std::size_t[memlen];
		std::copy(other.pMem, other.pMem + memlen, pMem);
	}

	bitfield::~bitfield()
	{
		delete[] pMem;
	}

	void bitfield::set(std::size_t idx, bool val)
	{
		if (idx < 0 || idx > maxlen)
			throw std::length_error(LENGTH_ERROR);

		if (val)
			pMem[mem_index(idx)] |= mem_mask(idx);
		else
			pMem[mem_index(idx)] &= ~mem_mask(idx);
	}

	bool bitfield::get(std::size_t idx) const
	{
		if (idx < 0 || idx > maxlen)
			throw std::length_error(LENGTH_ERROR);

		return (pMem[mem_index(idx)] & mem_mask(idx)) != 0;
	}

	bitfield::reference bitfield::operator[](std::size_t idx)
	{
		if (idx < 0 || idx > maxlen)
			throw std::length_error(LENGTH_ERROR);

		return reference(*this, idx);
	}

	std::size_t bitfield::size() const noexcept
	{
		return bitlen;
	}

	std::size_t bitfield::nonzero_count() noexcept
	{
		std::size_t count = 0;

		for (std::size_t i = 0; i < bitlen; i++)
			if ((*this)[i])
				count++;

		return count;
	}

	std::vector<std::size_t> bitfield::eratosthenes()
	{
		if (bitlen < 2)
			return {};

		for (std::size_t i = 2; i * i <= bitlen; i++)
			if ((*this)[i - 1] == false)
				for (std::size_t j = i * i; j <= bitlen; j += i)
					(*this)[j - 1] = true;

		std::vector<std::size_t> primes;

		for (std::size_t i = 2; i <= bitlen; i++)
			if (!(*this)[i - 1])
				primes.push_back(i);

		return primes;
	}

	std::size_t bitfield::mem_index(std::size_t n) const
	{
		return n / (sizeof(std::size_t) * 8);
	}

	std::size_t bitfield::mem_mask(std::size_t n) const
	{
		return static_cast<std::size_t>(1 << (n % (sizeof(std::size_t) * 8)));
	}

} // namespace lab
