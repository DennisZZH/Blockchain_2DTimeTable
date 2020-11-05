// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Msg_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Msg_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Msg_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Msg_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Msg_2eproto;
class application_msg_t;
class application_msg_tDefaultTypeInternal;
extern application_msg_tDefaultTypeInternal _application_msg_t_default_instance_;
class timetable_msg_t;
class timetable_msg_tDefaultTypeInternal;
extern timetable_msg_tDefaultTypeInternal _timetable_msg_t_default_instance_;
class transaction_msg_t;
class transaction_msg_tDefaultTypeInternal;
extern transaction_msg_tDefaultTypeInternal _transaction_msg_t_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::application_msg_t* Arena::CreateMaybeMessage<::application_msg_t>(Arena*);
template<> ::timetable_msg_t* Arena::CreateMaybeMessage<::timetable_msg_t>(Arena*);
template<> ::transaction_msg_t* Arena::CreateMaybeMessage<::transaction_msg_t>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class transaction_msg_t :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:transaction_msg_t) */ {
 public:
  transaction_msg_t();
  virtual ~transaction_msg_t();

  transaction_msg_t(const transaction_msg_t& from);
  transaction_msg_t(transaction_msg_t&& from) noexcept
    : transaction_msg_t() {
    *this = ::std::move(from);
  }

  inline transaction_msg_t& operator=(const transaction_msg_t& from) {
    CopyFrom(from);
    return *this;
  }
  inline transaction_msg_t& operator=(transaction_msg_t&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const transaction_msg_t& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const transaction_msg_t* internal_default_instance() {
    return reinterpret_cast<const transaction_msg_t*>(
               &_transaction_msg_t_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(transaction_msg_t& a, transaction_msg_t& b) {
    a.Swap(&b);
  }
  inline void Swap(transaction_msg_t* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline transaction_msg_t* New() const final {
    return CreateMaybeMessage<transaction_msg_t>(nullptr);
  }

  transaction_msg_t* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<transaction_msg_t>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const transaction_msg_t& from);
  void MergeFrom(const transaction_msg_t& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(transaction_msg_t* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "transaction_msg_t";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Msg_2eproto);
    return ::descriptor_table_Msg_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSenderIdFieldNumber = 1,
    kRecverIdFieldNumber = 2,
    kAmtFieldNumber = 3,
    kClockFieldNumber = 4,
  };
  // required uint32 sender_id = 1;
  bool has_sender_id() const;
  private:
  bool _internal_has_sender_id() const;
  public:
  void clear_sender_id();
  ::PROTOBUF_NAMESPACE_ID::uint32 sender_id() const;
  void set_sender_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_sender_id() const;
  void _internal_set_sender_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // required uint32 recver_id = 2;
  bool has_recver_id() const;
  private:
  bool _internal_has_recver_id() const;
  public:
  void clear_recver_id();
  ::PROTOBUF_NAMESPACE_ID::uint32 recver_id() const;
  void set_recver_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_recver_id() const;
  void _internal_set_recver_id(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // required float amt = 3;
  bool has_amt() const;
  private:
  bool _internal_has_amt() const;
  public:
  void clear_amt();
  float amt() const;
  void set_amt(float value);
  private:
  float _internal_amt() const;
  void _internal_set_amt(float value);
  public:

  // required uint32 clock = 4;
  bool has_clock() const;
  private:
  bool _internal_has_clock() const;
  public:
  void clear_clock();
  ::PROTOBUF_NAMESPACE_ID::uint32 clock() const;
  void set_clock(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_clock() const;
  void _internal_set_clock(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:transaction_msg_t)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 sender_id_;
  ::PROTOBUF_NAMESPACE_ID::uint32 recver_id_;
  float amt_;
  ::PROTOBUF_NAMESPACE_ID::uint32 clock_;
  friend struct ::TableStruct_Msg_2eproto;
};
// -------------------------------------------------------------------

class timetable_msg_t :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:timetable_msg_t) */ {
 public:
  timetable_msg_t();
  virtual ~timetable_msg_t();

  timetable_msg_t(const timetable_msg_t& from);
  timetable_msg_t(timetable_msg_t&& from) noexcept
    : timetable_msg_t() {
    *this = ::std::move(from);
  }

  inline timetable_msg_t& operator=(const timetable_msg_t& from) {
    CopyFrom(from);
    return *this;
  }
  inline timetable_msg_t& operator=(timetable_msg_t&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const timetable_msg_t& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const timetable_msg_t* internal_default_instance() {
    return reinterpret_cast<const timetable_msg_t*>(
               &_timetable_msg_t_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(timetable_msg_t& a, timetable_msg_t& b) {
    a.Swap(&b);
  }
  inline void Swap(timetable_msg_t* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline timetable_msg_t* New() const final {
    return CreateMaybeMessage<timetable_msg_t>(nullptr);
  }

  timetable_msg_t* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<timetable_msg_t>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const timetable_msg_t& from);
  void MergeFrom(const timetable_msg_t& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(timetable_msg_t* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "timetable_msg_t";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Msg_2eproto);
    return ::descriptor_table_Msg_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTimeFieldNumber = 1,
  };
  // repeated uint32 time = 1;
  int time_size() const;
  private:
  int _internal_time_size() const;
  public:
  void clear_time();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_time(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_time() const;
  void _internal_add_time(::PROTOBUF_NAMESPACE_ID::uint32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_time();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint32 time(int index) const;
  void set_time(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_time(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      time() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_time();

  // @@protoc_insertion_point(class_scope:timetable_msg_t)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > time_;
  friend struct ::TableStruct_Msg_2eproto;
};
// -------------------------------------------------------------------

class application_msg_t :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:application_msg_t) */ {
 public:
  application_msg_t();
  virtual ~application_msg_t();

  application_msg_t(const application_msg_t& from);
  application_msg_t(application_msg_t&& from) noexcept
    : application_msg_t() {
    *this = ::std::move(from);
  }

  inline application_msg_t& operator=(const application_msg_t& from) {
    CopyFrom(from);
    return *this;
  }
  inline application_msg_t& operator=(application_msg_t&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const application_msg_t& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const application_msg_t* internal_default_instance() {
    return reinterpret_cast<const application_msg_t*>(
               &_application_msg_t_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(application_msg_t& a, application_msg_t& b) {
    a.Swap(&b);
  }
  inline void Swap(application_msg_t* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline application_msg_t* New() const final {
    return CreateMaybeMessage<application_msg_t>(nullptr);
  }

  application_msg_t* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<application_msg_t>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const application_msg_t& from);
  void MergeFrom(const application_msg_t& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(application_msg_t* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "application_msg_t";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Msg_2eproto);
    return ::descriptor_table_Msg_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLogFieldNumber = 3,
    kTimetableFieldNumber = 2,
    kSenderIdFieldNumber = 1,
  };
  // repeated .transaction_msg_t log = 3;
  int log_size() const;
  private:
  int _internal_log_size() const;
  public:
  void clear_log();
  ::transaction_msg_t* mutable_log(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::transaction_msg_t >*
      mutable_log();
  private:
  const ::transaction_msg_t& _internal_log(int index) const;
  ::transaction_msg_t* _internal_add_log();
  public:
  const ::transaction_msg_t& log(int index) const;
  ::transaction_msg_t* add_log();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::transaction_msg_t >&
      log() const;

  // required .timetable_msg_t timetable = 2;
  bool has_timetable() const;
  private:
  bool _internal_has_timetable() const;
  public:
  void clear_timetable();
  const ::timetable_msg_t& timetable() const;
  ::timetable_msg_t* release_timetable();
  ::timetable_msg_t* mutable_timetable();
  void set_allocated_timetable(::timetable_msg_t* timetable);
  private:
  const ::timetable_msg_t& _internal_timetable() const;
  ::timetable_msg_t* _internal_mutable_timetable();
  public:

  // required int32 sender_id = 1;
  bool has_sender_id() const;
  private:
  bool _internal_has_sender_id() const;
  public:
  void clear_sender_id();
  ::PROTOBUF_NAMESPACE_ID::int32 sender_id() const;
  void set_sender_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_sender_id() const;
  void _internal_set_sender_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:application_msg_t)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::transaction_msg_t > log_;
  ::timetable_msg_t* timetable_;
  ::PROTOBUF_NAMESPACE_ID::int32 sender_id_;
  friend struct ::TableStruct_Msg_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// transaction_msg_t

// required uint32 sender_id = 1;
inline bool transaction_msg_t::_internal_has_sender_id() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool transaction_msg_t::has_sender_id() const {
  return _internal_has_sender_id();
}
inline void transaction_msg_t::clear_sender_id() {
  sender_id_ = 0u;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 transaction_msg_t::_internal_sender_id() const {
  return sender_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 transaction_msg_t::sender_id() const {
  // @@protoc_insertion_point(field_get:transaction_msg_t.sender_id)
  return _internal_sender_id();
}
inline void transaction_msg_t::_internal_set_sender_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000001u;
  sender_id_ = value;
}
inline void transaction_msg_t::set_sender_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_sender_id(value);
  // @@protoc_insertion_point(field_set:transaction_msg_t.sender_id)
}

// required uint32 recver_id = 2;
inline bool transaction_msg_t::_internal_has_recver_id() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool transaction_msg_t::has_recver_id() const {
  return _internal_has_recver_id();
}
inline void transaction_msg_t::clear_recver_id() {
  recver_id_ = 0u;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 transaction_msg_t::_internal_recver_id() const {
  return recver_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 transaction_msg_t::recver_id() const {
  // @@protoc_insertion_point(field_get:transaction_msg_t.recver_id)
  return _internal_recver_id();
}
inline void transaction_msg_t::_internal_set_recver_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000002u;
  recver_id_ = value;
}
inline void transaction_msg_t::set_recver_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_recver_id(value);
  // @@protoc_insertion_point(field_set:transaction_msg_t.recver_id)
}

// required float amt = 3;
inline bool transaction_msg_t::_internal_has_amt() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool transaction_msg_t::has_amt() const {
  return _internal_has_amt();
}
inline void transaction_msg_t::clear_amt() {
  amt_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline float transaction_msg_t::_internal_amt() const {
  return amt_;
}
inline float transaction_msg_t::amt() const {
  // @@protoc_insertion_point(field_get:transaction_msg_t.amt)
  return _internal_amt();
}
inline void transaction_msg_t::_internal_set_amt(float value) {
  _has_bits_[0] |= 0x00000004u;
  amt_ = value;
}
inline void transaction_msg_t::set_amt(float value) {
  _internal_set_amt(value);
  // @@protoc_insertion_point(field_set:transaction_msg_t.amt)
}

// required uint32 clock = 4;
inline bool transaction_msg_t::_internal_has_clock() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool transaction_msg_t::has_clock() const {
  return _internal_has_clock();
}
inline void transaction_msg_t::clear_clock() {
  clock_ = 0u;
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 transaction_msg_t::_internal_clock() const {
  return clock_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 transaction_msg_t::clock() const {
  // @@protoc_insertion_point(field_get:transaction_msg_t.clock)
  return _internal_clock();
}
inline void transaction_msg_t::_internal_set_clock(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000008u;
  clock_ = value;
}
inline void transaction_msg_t::set_clock(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_clock(value);
  // @@protoc_insertion_point(field_set:transaction_msg_t.clock)
}

// -------------------------------------------------------------------

// timetable_msg_t

// repeated uint32 time = 1;
inline int timetable_msg_t::_internal_time_size() const {
  return time_.size();
}
inline int timetable_msg_t::time_size() const {
  return _internal_time_size();
}
inline void timetable_msg_t::clear_time() {
  time_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 timetable_msg_t::_internal_time(int index) const {
  return time_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 timetable_msg_t::time(int index) const {
  // @@protoc_insertion_point(field_get:timetable_msg_t.time)
  return _internal_time(index);
}
inline void timetable_msg_t::set_time(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  time_.Set(index, value);
  // @@protoc_insertion_point(field_set:timetable_msg_t.time)
}
inline void timetable_msg_t::_internal_add_time(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  time_.Add(value);
}
inline void timetable_msg_t::add_time(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_add_time(value);
  // @@protoc_insertion_point(field_add:timetable_msg_t.time)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
timetable_msg_t::_internal_time() const {
  return time_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
timetable_msg_t::time() const {
  // @@protoc_insertion_point(field_list:timetable_msg_t.time)
  return _internal_time();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
timetable_msg_t::_internal_mutable_time() {
  return &time_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
timetable_msg_t::mutable_time() {
  // @@protoc_insertion_point(field_mutable_list:timetable_msg_t.time)
  return _internal_mutable_time();
}

// -------------------------------------------------------------------

// application_msg_t

// required int32 sender_id = 1;
inline bool application_msg_t::_internal_has_sender_id() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool application_msg_t::has_sender_id() const {
  return _internal_has_sender_id();
}
inline void application_msg_t::clear_sender_id() {
  sender_id_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 application_msg_t::_internal_sender_id() const {
  return sender_id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 application_msg_t::sender_id() const {
  // @@protoc_insertion_point(field_get:application_msg_t.sender_id)
  return _internal_sender_id();
}
inline void application_msg_t::_internal_set_sender_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  sender_id_ = value;
}
inline void application_msg_t::set_sender_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_sender_id(value);
  // @@protoc_insertion_point(field_set:application_msg_t.sender_id)
}

// required .timetable_msg_t timetable = 2;
inline bool application_msg_t::_internal_has_timetable() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || timetable_ != nullptr);
  return value;
}
inline bool application_msg_t::has_timetable() const {
  return _internal_has_timetable();
}
inline void application_msg_t::clear_timetable() {
  if (timetable_ != nullptr) timetable_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::timetable_msg_t& application_msg_t::_internal_timetable() const {
  const ::timetable_msg_t* p = timetable_;
  return p != nullptr ? *p : *reinterpret_cast<const ::timetable_msg_t*>(
      &::_timetable_msg_t_default_instance_);
}
inline const ::timetable_msg_t& application_msg_t::timetable() const {
  // @@protoc_insertion_point(field_get:application_msg_t.timetable)
  return _internal_timetable();
}
inline ::timetable_msg_t* application_msg_t::release_timetable() {
  // @@protoc_insertion_point(field_release:application_msg_t.timetable)
  _has_bits_[0] &= ~0x00000001u;
  ::timetable_msg_t* temp = timetable_;
  timetable_ = nullptr;
  return temp;
}
inline ::timetable_msg_t* application_msg_t::_internal_mutable_timetable() {
  _has_bits_[0] |= 0x00000001u;
  if (timetable_ == nullptr) {
    auto* p = CreateMaybeMessage<::timetable_msg_t>(GetArenaNoVirtual());
    timetable_ = p;
  }
  return timetable_;
}
inline ::timetable_msg_t* application_msg_t::mutable_timetable() {
  // @@protoc_insertion_point(field_mutable:application_msg_t.timetable)
  return _internal_mutable_timetable();
}
inline void application_msg_t::set_allocated_timetable(::timetable_msg_t* timetable) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete timetable_;
  }
  if (timetable) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      timetable = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, timetable, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  timetable_ = timetable;
  // @@protoc_insertion_point(field_set_allocated:application_msg_t.timetable)
}

// repeated .transaction_msg_t log = 3;
inline int application_msg_t::_internal_log_size() const {
  return log_.size();
}
inline int application_msg_t::log_size() const {
  return _internal_log_size();
}
inline void application_msg_t::clear_log() {
  log_.Clear();
}
inline ::transaction_msg_t* application_msg_t::mutable_log(int index) {
  // @@protoc_insertion_point(field_mutable:application_msg_t.log)
  return log_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::transaction_msg_t >*
application_msg_t::mutable_log() {
  // @@protoc_insertion_point(field_mutable_list:application_msg_t.log)
  return &log_;
}
inline const ::transaction_msg_t& application_msg_t::_internal_log(int index) const {
  return log_.Get(index);
}
inline const ::transaction_msg_t& application_msg_t::log(int index) const {
  // @@protoc_insertion_point(field_get:application_msg_t.log)
  return _internal_log(index);
}
inline ::transaction_msg_t* application_msg_t::_internal_add_log() {
  return log_.Add();
}
inline ::transaction_msg_t* application_msg_t::add_log() {
  // @@protoc_insertion_point(field_add:application_msg_t.log)
  return _internal_add_log();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::transaction_msg_t >&
application_msg_t::log() const {
  // @@protoc_insertion_point(field_list:application_msg_t.log)
  return log_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Msg_2eproto
