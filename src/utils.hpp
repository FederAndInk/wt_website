/**
 * @file utils.hpp
 * @author FederAndInk<Ludovic Jozeau> (federandink@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-09
 * 
 * @copyright Copyright (c) 2020
 * 
 * @license This project is released under the MIT License.
 */
#pragma once
#include <concepts>
#include <cstddef>
#include <type_traits>
namespace fai
{
template <typename T>
class loaned_ptr
{
private:
  T* ptr{};

public:
  using element_type = T;
  using pointer = T*;

  constexpr loaned_ptr() noexcept = default;
  explicit(false) constexpr loaned_ptr(std::nullptr_t) noexcept : ptr() {}

  explicit constexpr loaned_ptr(pointer ptr) noexcept : ptr(ptr) {}

  template <typename U>
  explicit(false) constexpr loaned_ptr(loaned_ptr<U> other) noexcept
    requires(std::convertible_to<std::add_pointer_t<U>, pointer>)
    : ptr(other.get())

  {
  }

  pointer operator->() const noexcept
  {
    return get();
  }

  constexpr T& operator*() const noexcept
  {
    return *get();
  }

  constexpr pointer get() const noexcept
  {
    return ptr;
  }

  constexpr pointer to_raw() const noexcept
  {
    return get();
  }

  constexpr operator bool() const noexcept
  {
    return get() != nullptr;
  }

  constexpr explicit operator pointer() const noexcept
  {
    return get();
  }
};

template <typename T>
concept smart_ptr = requires(T t)
{
  typename T::element_type;
  {
    t.get()
  }
  ->std::same_as<std::add_pointer_t<typename T::element_type>>;
  {
    t.operator->()
  }
  ->std::same_as<std::add_pointer_t<typename T::element_type>>;
  std::is_pointer_v<decltype(t.get())>;
  {
    *t
  }
  ->std::same_as<std::add_lvalue_reference_t<typename T::element_type>>;
};

template <smart_ptr T>
loaned_ptr<typename T::element_type> loan(T& ptr)
{
  return loaned_ptr{ptr.get()};
}

template <typename T>
loaned_ptr<T> loan(T* ptr)
{
  return loaned_ptr{ptr};
}
} // namespace fai
