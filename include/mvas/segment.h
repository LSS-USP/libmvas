#ifndef __SEGMENT_H__
#define __SEGMENT_H__


#include <mvas/vas.h>

#include <linux/types.h>
#include <linux/vas.h>

#include <fcntl.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SYS_vas_seg_create __NR_vas_seg_create
#define SYS_vas_seg_delete __NR_vas_seg_delete
#define SYS_vas_seg_find __NR_vas_seg_find
#define SYS_vas_seg_attach __NR_vas_seg_attach
#define SYS_vas_seg_detach __NR_vas_seg_detach
#define SYS_vas_seg_getattr __NR_vas_seg_getattr
#define SYS_vas_seg_setattr __NR_vas_seg_setattr

typedef int segid_t;

/**
 * Create a new segment.
 *
 * @param[in] name:         The name which the segment should have.
 * @param[in] start:        The virtual address where the segment should start.
 * @param[in] end:          The virtual address where the segment should end.
 * @param[in] mode:         The access control list for the segment defining
 *                          which users are allowed to use the segment in which
 *                          way. See creat(3) for more information about how to
 *                          specify the mode.
 *
 * @returns:                The ID of the segment on succes, -1 on failure
 *                          (setting errno).
 **/
extern segid_t segment_create(const char * const name, unsigned long start,
                              unsigned long end, mode_t mode);

/**
 * Create a new segment - specifying its size.
 *
 * @see segment_create
 *
 * @param[in] size:         The size of the resulting segment in bytes.
 **/
extern segid_t segment_create_sz(const char * const name, unsigned long start,
                                 unsigned long size, mode_t mode);

/**
 * Delete an existing segment again.
 *
 * @param[in] sid:          The ID of the segment that should be deleted.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int segment_delete(segid_t sid);

/**
 * Find the ID of the segment with the given name.
 *
 * @param[in] name:         The name of the segment for which the ID should be
 *                          found.
 *
 * @returns:                The ID of the segment on success, -1 on failure
 *                          (setting errno).
 **/
extern segid_t segment_find(const char * const name);

/**
 * Attach a segment to a VAS.
 *
 * @param[in] vid:          The ID of the VAS to which the segment should be
 *                          attached.
 * @param[in] sid:          The ID of the segment that should be attached.
 * @param[in] type:         The way in which the segment should be attached.
 *                          This must be either O_RDONLY, O_RDWR or O_WRONLY.
 *                          See open(3) for more information about the different
 *                          types available.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int segment_attach(vasid_t vid, segid_t sid, int type);

/**
 * Detach a segment from a VAS again.
 *
 * @param[in] vid:          The ID of the VAS from which the segment should be
 *                          detached.
 * @param[in] sid:          The ID of the segment that should be detached.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int segment_detach(vasid_t vid, segid_t sid);

/**
 * Get the attributes of a segment.
 *
 * @param[in] sid:          The ID of the segment of which the attributes
 *                          should be retrieved.
 * @param[out] attr:        The pointer to the data structure where the
 *                          attributes should be saved in.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int segment_getattr(segid_t sid, struct vas_seg_attr * const attr);

/**
 * Change the attributes of a segment.
 *
 * @param[in] sid:          The ID of the segment of which the attributes
 *                          should be changed.
 * @param[in] attr:         The pointer to the data structure containing the
 *                          new attributes that should be set.
 *
 * @returns:                0 on success, -1 on failure (setting errno).
 **/
extern int segment_setattr(segid_t sid,
                           const struct vas_seg_attr * const attr);

#ifdef __cplusplus
}
#endif

#endif /* __SEGMENT_H__ */
