package com.wison.ffmpeg

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ImageView
import com.wison.ffmpeg.player.MediaView
import kotlin.concurrent.thread

class DetailActivity : AppCompatActivity(), View.OnClickListener {

    private lateinit var mMediaView: MediaView
    private lateinit var playIV: ImageView

    companion object {
        const val INTENT_VIDEO_URI = "video_info"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_detail)

        mMediaView = findViewById(R.id.media_view)
        playIV = findViewById(R.id.play_iv)

        val info: VideoInfo? = intent.getParcelableExtra(EditActivity.INTENT_VIDEO_URI) as VideoInfo?
        mMediaView.setPath(info?.path)
        playIV.setOnClickListener(this)
    }

    override fun onClick(v: View?) {
        thread(start = true) {
            mMediaView.play()
        }
    }


}