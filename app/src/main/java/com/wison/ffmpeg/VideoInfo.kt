package com.wison.ffmpeg

import android.net.Uri
import android.os.Parcelable
import kotlinx.parcelize.Parcelize
import java.io.Serializable

/**
 * Created by ZhangWeiRong on 2021/5/11.
 */
@Parcelize
data class VideoInfo(val uri: Uri, val id: Long, val name: String, val path: String, val duration: Long, val size: Int): Parcelable