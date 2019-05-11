#pragma once

#ifndef BITFIELD_HPP
#define BITFIELD_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

static constexpr std::size_t maxlen = 10000000;
#define LENGTH_ERROR "A bit field must have length more than 0 and less than 10000000."

namespace lab {

	class bitfield {

	public:
		// Proxy class providing access to a particular bit.
		class reference
		{
			friend bitfield;

		public:
			reference& operator=(bool val) noexcept {
				p_bitfield->set(m_idx, val);
				return *this;
			}

			operator bool() const noexcept {
				return p_bitfield->get(m_idx);
			}

		private:
			reference(bitfield& bf, std::size_t idx)
				: p_bitfield(&bf), m_idx(idx)
			{
			}

			bitfield *p_bitfield;
			std::size_t m_idx;
		};

		explicit bitfield(std::size_t len);
		bitfield(const bitfield& other);
		~bitfield();

		void set(std::size_t idx, bool val = true);
		bool get(std::size_t idx) const;
		reference operator[](std::size_t idx);

		std::size_t size() const noexcept;
		std::size_t nonzero_count() noexcept;
		std::vector<std::size_t> eratosthenes();

	private:
		std::size_t *pMem;
		std::size_t bitlen;
		std::size_t memlen;

		std::size_t mem_index(std::size_t n) const;
		std::size_t mem_mask(std::size_t n) const;
	};

} // namespace lab

#endif BITFIELD_HPP
