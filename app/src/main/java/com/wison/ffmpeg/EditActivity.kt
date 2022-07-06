package com.wison.ffmpeg

import android.media.MediaMetadataRetriever
import android.os.Bundle
import android.view.View
import android.widget.ImageView
import android.widget.TextView
import android.widget.VideoView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class EditActivity : AppCompatActivity(), View.OnClickListener {

    companion object {
        const val INTENT_VIDEO_URI = "video_info"
    }

    private val retriever = MediaMetadataRetriever()

    private lateinit var videoView: VideoView
    private lateinit var previewList: RecyclerView
    private lateinit var playIV: ImageView
    private lateinit var videoIV: ImageView
    private lateinit var filterIV: ImageView
    private lateinit var cancelTV: TextView
    private lateinit var saveTV: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit)
        videoView = findViewById(R.id.video_view)
        previewList = findViewById(R.id.preview_list)
        playIV = findViewById(R.id.play_iv)
        videoIV = findViewById(R.id.video_iv)
        filterIV = findViewById(R.id.filter_iv)
        cancelTV = findViewById(R.id.cancel_tv)
        saveTV = findViewById(R.id.save_tv)

        previewList.layoutManager = LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false)

        playIV.setOnClickListener(this)
        cancelTV.setOnClickListener(this)
        saveTV.setOnClickListener(this)

        val info: VideoInfo? = intent.getParcelableExtra(INTENT_VIDEO_URI) as VideoInfo?
        videoView.setVideoURI(info?.uri)

        retriever.setDataSource(this, info?.uri)
    }

    override fun onClick(v: View?) {
        when (v) {
            playIV -> {
                videoView.start()
            }
            cancelTV -> {
                finish()
            }
            saveTV -> {

            }
        }
    }

}