/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.yaz4j.jni;

public class yaz4jlib implements yaz4jlibConstants {
  public static SWIGTYPE_p_int new_intp() {
    long cPtr = yaz4jlibJNI.new_intp();
    return (cPtr == 0) ? null : new SWIGTYPE_p_int(cPtr, false);
  }

  public static SWIGTYPE_p_int copy_intp(int value) {
    long cPtr = yaz4jlibJNI.copy_intp(value);
    return (cPtr == 0) ? null : new SWIGTYPE_p_int(cPtr, false);
  }

  public static void delete_intp(SWIGTYPE_p_int self) {
    yaz4jlibJNI.delete_intp(SWIGTYPE_p_int.getCPtr(self));
  }

  public static void intp_assign(SWIGTYPE_p_int self, int value) {
    yaz4jlibJNI.intp_assign(SWIGTYPE_p_int.getCPtr(self), value);
  }

  public static int intp_value(SWIGTYPE_p_int self) {
    return yaz4jlibJNI.intp_value(SWIGTYPE_p_int.getCPtr(self));
  }

  public static byte[] ZOOM_record_get_bytes(SWIGTYPE_p_ZOOM_record_p rec, String type, SWIGTYPE_p_int len) { return yaz4jlibJNI.ZOOM_record_get_bytes(SWIGTYPE_p_ZOOM_record_p.getCPtr(rec), type, SWIGTYPE_p_int.getCPtr(len)); }

  public static SWIGTYPE_p_ZOOM_connection_p ZOOM_connection_new(String host, int portnum) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_new(host, portnum);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_connection_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_connection_p ZOOM_connection_create(SWIGTYPE_p_ZOOM_options_p options) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_create(SWIGTYPE_p_ZOOM_options_p.getCPtr(options));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_connection_p(cPtr, false);
  }

  public static void ZOOM_connection_connect(SWIGTYPE_p_ZOOM_connection_p c, String host, int portnum) {
    yaz4jlibJNI.ZOOM_connection_connect(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), host, portnum);
  }

  public static void ZOOM_connection_destroy(SWIGTYPE_p_ZOOM_connection_p c) {
    yaz4jlibJNI.ZOOM_connection_destroy(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c));
  }

  public static String ZOOM_connection_option_get(SWIGTYPE_p_ZOOM_connection_p c, String key) {
    return yaz4jlibJNI.ZOOM_connection_option_get(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), key);
  }

  public static String ZOOM_connection_option_getl(SWIGTYPE_p_ZOOM_connection_p c, String key, SWIGTYPE_p_int lenp) {
    return yaz4jlibJNI.ZOOM_connection_option_getl(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), key, SWIGTYPE_p_int.getCPtr(lenp));
  }

  public static void ZOOM_connection_option_set(SWIGTYPE_p_ZOOM_connection_p c, String key, String val) {
    yaz4jlibJNI.ZOOM_connection_option_set(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), key, val);
  }

  public static void ZOOM_connection_option_setl(SWIGTYPE_p_ZOOM_connection_p c, String key, String val, int len) {
    yaz4jlibJNI.ZOOM_connection_option_setl(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), key, val, len);
  }

  public static int ZOOM_connection_error(SWIGTYPE_p_ZOOM_connection_p c, SWIGTYPE_p_p_char cp, SWIGTYPE_p_p_char addinfo) {
    return yaz4jlibJNI.ZOOM_connection_error(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), SWIGTYPE_p_p_char.getCPtr(cp), SWIGTYPE_p_p_char.getCPtr(addinfo));
  }

  public static int ZOOM_connection_error_x(SWIGTYPE_p_ZOOM_connection_p c, SWIGTYPE_p_p_char cp, SWIGTYPE_p_p_char addinfo, SWIGTYPE_p_p_char diagset) {
    return yaz4jlibJNI.ZOOM_connection_error_x(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), SWIGTYPE_p_p_char.getCPtr(cp), SWIGTYPE_p_p_char.getCPtr(addinfo), SWIGTYPE_p_p_char.getCPtr(diagset));
  }

  public static int ZOOM_connection_errcode(SWIGTYPE_p_ZOOM_connection_p c) {
    return yaz4jlibJNI.ZOOM_connection_errcode(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c));
  }

  public static String ZOOM_connection_errmsg(SWIGTYPE_p_ZOOM_connection_p c) {
    return yaz4jlibJNI.ZOOM_connection_errmsg(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c));
  }

  public static String ZOOM_connection_addinfo(SWIGTYPE_p_ZOOM_connection_p c) {
    return yaz4jlibJNI.ZOOM_connection_addinfo(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c));
  }

  public static String ZOOM_connection_diagset(SWIGTYPE_p_ZOOM_connection_p c) {
    return yaz4jlibJNI.ZOOM_connection_diagset(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c));
  }

  public static String ZOOM_diag_str(int error) {
    return yaz4jlibJNI.ZOOM_diag_str(error);
  }

  public static int ZOOM_connection_last_event(SWIGTYPE_p_ZOOM_connection_p cs) {
    return yaz4jlibJNI.ZOOM_connection_last_event(SWIGTYPE_p_ZOOM_connection_p.getCPtr(cs));
  }

  public static SWIGTYPE_p_ZOOM_resultset_p ZOOM_connection_search(SWIGTYPE_p_ZOOM_connection_p arg0, SWIGTYPE_p_ZOOM_query_p q) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_search(SWIGTYPE_p_ZOOM_connection_p.getCPtr(arg0), SWIGTYPE_p_ZOOM_query_p.getCPtr(q));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_resultset_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_resultset_p ZOOM_connection_search_pqf(SWIGTYPE_p_ZOOM_connection_p c, String q) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_search_pqf(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), q);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_resultset_p(cPtr, false);
  }

  public static void ZOOM_resultset_destroy(SWIGTYPE_p_ZOOM_resultset_p r) {
    yaz4jlibJNI.ZOOM_resultset_destroy(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r));
  }

  public static String ZOOM_resultset_option_get(SWIGTYPE_p_ZOOM_resultset_p r, String key) {
    return yaz4jlibJNI.ZOOM_resultset_option_get(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r), key);
  }

  public static void ZOOM_resultset_option_set(SWIGTYPE_p_ZOOM_resultset_p r, String key, String val) {
    yaz4jlibJNI.ZOOM_resultset_option_set(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r), key, val);
  }

  public static long ZOOM_resultset_size(SWIGTYPE_p_ZOOM_resultset_p r) {
    return yaz4jlibJNI.ZOOM_resultset_size(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r));
  }

  public static void ZOOM_resultset_records(SWIGTYPE_p_ZOOM_resultset_p r, SWIGTYPE_p_p_ZOOM_record_p recs, long start, long count) {
    yaz4jlibJNI.ZOOM_resultset_records(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r), SWIGTYPE_p_p_ZOOM_record_p.getCPtr(recs), start, count);
  }

  public static SWIGTYPE_p_ZOOM_record_p ZOOM_resultset_record(SWIGTYPE_p_ZOOM_resultset_p s, long pos) {
    long cPtr = yaz4jlibJNI.ZOOM_resultset_record(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(s), pos);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_record_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_record_p ZOOM_resultset_record_immediate(SWIGTYPE_p_ZOOM_resultset_p s, long pos) {
    long cPtr = yaz4jlibJNI.ZOOM_resultset_record_immediate(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(s), pos);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_record_p(cPtr, false);
  }

  public static void ZOOM_resultset_cache_reset(SWIGTYPE_p_ZOOM_resultset_p r) {
    yaz4jlibJNI.ZOOM_resultset_cache_reset(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r));
  }

  public static String ZOOM_record_get(SWIGTYPE_p_ZOOM_record_p rec, String type, SWIGTYPE_p_int len) {
    return yaz4jlibJNI.ZOOM_record_get(SWIGTYPE_p_ZOOM_record_p.getCPtr(rec), type, SWIGTYPE_p_int.getCPtr(len));
  }

  public static void ZOOM_record_destroy(SWIGTYPE_p_ZOOM_record_p rec) {
    yaz4jlibJNI.ZOOM_record_destroy(SWIGTYPE_p_ZOOM_record_p.getCPtr(rec));
  }

  public static SWIGTYPE_p_ZOOM_record_p ZOOM_record_clone(SWIGTYPE_p_ZOOM_record_p srec) {
    long cPtr = yaz4jlibJNI.ZOOM_record_clone(SWIGTYPE_p_ZOOM_record_p.getCPtr(srec));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_record_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_query_p ZOOM_query_create() {
    long cPtr = yaz4jlibJNI.ZOOM_query_create();
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_query_p(cPtr, false);
  }

  public static void ZOOM_query_destroy(SWIGTYPE_p_ZOOM_query_p s) {
    yaz4jlibJNI.ZOOM_query_destroy(SWIGTYPE_p_ZOOM_query_p.getCPtr(s));
  }

  public static int ZOOM_query_cql(SWIGTYPE_p_ZOOM_query_p s, String str) {
    return yaz4jlibJNI.ZOOM_query_cql(SWIGTYPE_p_ZOOM_query_p.getCPtr(s), str);
  }

  public static int ZOOM_query_cql2rpn(SWIGTYPE_p_ZOOM_query_p s, String str, SWIGTYPE_p_ZOOM_connection_p conn) {
    return yaz4jlibJNI.ZOOM_query_cql2rpn(SWIGTYPE_p_ZOOM_query_p.getCPtr(s), str, SWIGTYPE_p_ZOOM_connection_p.getCPtr(conn));
  }

  public static int ZOOM_query_ccl2rpn(SWIGTYPE_p_ZOOM_query_p s, String query_str, String config, SWIGTYPE_p_int ccl_error, SWIGTYPE_p_p_char error_string, SWIGTYPE_p_int error_pos) {
    return yaz4jlibJNI.ZOOM_query_ccl2rpn(SWIGTYPE_p_ZOOM_query_p.getCPtr(s), query_str, config, SWIGTYPE_p_int.getCPtr(ccl_error), SWIGTYPE_p_p_char.getCPtr(error_string), SWIGTYPE_p_int.getCPtr(error_pos));
  }

  public static int ZOOM_query_prefix(SWIGTYPE_p_ZOOM_query_p s, String str) {
    return yaz4jlibJNI.ZOOM_query_prefix(SWIGTYPE_p_ZOOM_query_p.getCPtr(s), str);
  }

  public static int ZOOM_query_sortby(SWIGTYPE_p_ZOOM_query_p s, String criteria) {
    return yaz4jlibJNI.ZOOM_query_sortby(SWIGTYPE_p_ZOOM_query_p.getCPtr(s), criteria);
  }

  public static SWIGTYPE_p_ZOOM_scanset_p ZOOM_connection_scan(SWIGTYPE_p_ZOOM_connection_p c, String startterm) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_scan(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), startterm);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_scanset_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_scanset_p ZOOM_connection_scan1(SWIGTYPE_p_ZOOM_connection_p c, SWIGTYPE_p_ZOOM_query_p startterm) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_scan1(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), SWIGTYPE_p_ZOOM_query_p.getCPtr(startterm));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_scanset_p(cPtr, false);
  }

  public static String ZOOM_scanset_term(SWIGTYPE_p_ZOOM_scanset_p scan, long pos, SWIGTYPE_p_int occ, SWIGTYPE_p_int len) {
    return yaz4jlibJNI.ZOOM_scanset_term(SWIGTYPE_p_ZOOM_scanset_p.getCPtr(scan), pos, SWIGTYPE_p_int.getCPtr(occ), SWIGTYPE_p_int.getCPtr(len));
  }

  public static String ZOOM_scanset_display_term(SWIGTYPE_p_ZOOM_scanset_p scan, long pos, SWIGTYPE_p_int occ, SWIGTYPE_p_int len) {
    return yaz4jlibJNI.ZOOM_scanset_display_term(SWIGTYPE_p_ZOOM_scanset_p.getCPtr(scan), pos, SWIGTYPE_p_int.getCPtr(occ), SWIGTYPE_p_int.getCPtr(len));
  }

  public static long ZOOM_scanset_size(SWIGTYPE_p_ZOOM_scanset_p scan) {
    return yaz4jlibJNI.ZOOM_scanset_size(SWIGTYPE_p_ZOOM_scanset_p.getCPtr(scan));
  }

  public static void ZOOM_scanset_destroy(SWIGTYPE_p_ZOOM_scanset_p scan) {
    yaz4jlibJNI.ZOOM_scanset_destroy(SWIGTYPE_p_ZOOM_scanset_p.getCPtr(scan));
  }

  public static String ZOOM_scanset_option_get(SWIGTYPE_p_ZOOM_scanset_p scan, String key) {
    return yaz4jlibJNI.ZOOM_scanset_option_get(SWIGTYPE_p_ZOOM_scanset_p.getCPtr(scan), key);
  }

  public static void ZOOM_scanset_option_set(SWIGTYPE_p_ZOOM_scanset_p scan, String key, String val) {
    yaz4jlibJNI.ZOOM_scanset_option_set(SWIGTYPE_p_ZOOM_scanset_p.getCPtr(scan), key, val);
  }

  public static SWIGTYPE_p_ZOOM_package_p ZOOM_connection_package(SWIGTYPE_p_ZOOM_connection_p c, SWIGTYPE_p_ZOOM_options_p options) {
    long cPtr = yaz4jlibJNI.ZOOM_connection_package(SWIGTYPE_p_ZOOM_connection_p.getCPtr(c), SWIGTYPE_p_ZOOM_options_p.getCPtr(options));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_package_p(cPtr, false);
  }

  public static void ZOOM_package_destroy(SWIGTYPE_p_ZOOM_package_p p) {
    yaz4jlibJNI.ZOOM_package_destroy(SWIGTYPE_p_ZOOM_package_p.getCPtr(p));
  }

  public static void ZOOM_package_send(SWIGTYPE_p_ZOOM_package_p p, String type) {
    yaz4jlibJNI.ZOOM_package_send(SWIGTYPE_p_ZOOM_package_p.getCPtr(p), type);
  }

  public static String ZOOM_package_option_get(SWIGTYPE_p_ZOOM_package_p p, String key) {
    return yaz4jlibJNI.ZOOM_package_option_get(SWIGTYPE_p_ZOOM_package_p.getCPtr(p), key);
  }

  public static void ZOOM_package_option_set(SWIGTYPE_p_ZOOM_package_p p, String key, String val) {
    yaz4jlibJNI.ZOOM_package_option_set(SWIGTYPE_p_ZOOM_package_p.getCPtr(p), key, val);
  }

  public static void ZOOM_resultset_sort(SWIGTYPE_p_ZOOM_resultset_p r, String sort_type, String sort_spec) {
    yaz4jlibJNI.ZOOM_resultset_sort(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r), sort_type, sort_spec);
  }

  public static int ZOOM_resultset_sort1(SWIGTYPE_p_ZOOM_resultset_p r, String sort_type, String sort_spec) {
    return yaz4jlibJNI.ZOOM_resultset_sort1(SWIGTYPE_p_ZOOM_resultset_p.getCPtr(r), sort_type, sort_spec);
  }

  public static SWIGTYPE_p_f_p_void_p_q_const__char__p_char ZOOM_options_set_callback(SWIGTYPE_p_ZOOM_options_p opt, SWIGTYPE_p_f_p_void_p_q_const__char__p_char c, SWIGTYPE_p_void handle) {
    long cPtr = yaz4jlibJNI.ZOOM_options_set_callback(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), SWIGTYPE_p_f_p_void_p_q_const__char__p_char.getCPtr(c), SWIGTYPE_p_void.getCPtr(handle));
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_void_p_q_const__char__p_char(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_options_p ZOOM_options_create() {
    long cPtr = yaz4jlibJNI.ZOOM_options_create();
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_options_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_options_p ZOOM_options_create_with_parent(SWIGTYPE_p_ZOOM_options_p parent) {
    long cPtr = yaz4jlibJNI.ZOOM_options_create_with_parent(SWIGTYPE_p_ZOOM_options_p.getCPtr(parent));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_options_p(cPtr, false);
  }

  public static SWIGTYPE_p_ZOOM_options_p ZOOM_options_create_with_parent2(SWIGTYPE_p_ZOOM_options_p parent1, SWIGTYPE_p_ZOOM_options_p parent2) {
    long cPtr = yaz4jlibJNI.ZOOM_options_create_with_parent2(SWIGTYPE_p_ZOOM_options_p.getCPtr(parent1), SWIGTYPE_p_ZOOM_options_p.getCPtr(parent2));
    return (cPtr == 0) ? null : new SWIGTYPE_p_ZOOM_options_p(cPtr, false);
  }

  public static String ZOOM_options_get(SWIGTYPE_p_ZOOM_options_p opt, String name) {
    return yaz4jlibJNI.ZOOM_options_get(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name);
  }

  public static String ZOOM_options_getl(SWIGTYPE_p_ZOOM_options_p opt, String name, SWIGTYPE_p_int lenp) {
    return yaz4jlibJNI.ZOOM_options_getl(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name, SWIGTYPE_p_int.getCPtr(lenp));
  }

  public static void ZOOM_options_set(SWIGTYPE_p_ZOOM_options_p opt, String name, String v) {
    yaz4jlibJNI.ZOOM_options_set(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name, v);
  }

  public static void ZOOM_options_setl(SWIGTYPE_p_ZOOM_options_p opt, String name, String value, int len) {
    yaz4jlibJNI.ZOOM_options_setl(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name, value, len);
  }

  public static void ZOOM_options_destroy(SWIGTYPE_p_ZOOM_options_p opt) {
    yaz4jlibJNI.ZOOM_options_destroy(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt));
  }

  public static int ZOOM_options_get_bool(SWIGTYPE_p_ZOOM_options_p opt, String name, int defa) {
    return yaz4jlibJNI.ZOOM_options_get_bool(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name, defa);
  }

  public static int ZOOM_options_get_int(SWIGTYPE_p_ZOOM_options_p opt, String name, int defa) {
    return yaz4jlibJNI.ZOOM_options_get_int(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name, defa);
  }

  public static void ZOOM_options_set_int(SWIGTYPE_p_ZOOM_options_p opt, String name, int value) {
    yaz4jlibJNI.ZOOM_options_set_int(SWIGTYPE_p_ZOOM_options_p.getCPtr(opt), name, value);
  }

  public static int ZOOM_event(int no, SWIGTYPE_p_p_ZOOM_connection_p cs) {
    return yaz4jlibJNI.ZOOM_event(no, SWIGTYPE_p_p_ZOOM_connection_p.getCPtr(cs));
  }

}
