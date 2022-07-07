package com.wison.ffmpeg

import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide

/**
 * Created by Wison on 2021/5/11.
 */
class MediaAdapter(val data: List<VideoInfo>): RecyclerView.Adapter<MediaAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_video, parent, false)
        return ViewHolder(view)
    }

    override fun getItemCount(): Int {
        return data.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        Glide.with(holder.frameIV)
            .load(data[position].uri)
            .centerCrop()
            .into(holder.frameIV)
        holder.durationTV.text = durationToTime(data[position].duration)

        holder.frameIV.setOnClickListener {
            val intent = Intent()
            intent.putExtra(DetailActivity.INTENT_VIDEO_URI, data[position])
            intent.setClass(holder.frameIV.context, DetailActivity::class.java)
            holder.frameIV.context.startActivity(intent)
        }
    }

    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val frameIV: ImageView = itemView.findViewById(R.id.frame_iv)
        val durationTV: TextView = itemView.findViewById(R.id.duration_tv)
    }

    private fun durationToTime(duration: Long): String? {
        var seconds = duration / 1000
        val finalTimerString = StringBuilder()
        val minutes = seconds / 60
        seconds %= 60

        when {
            minutes >= 10 -> {
                finalTimerString.append(minutes)
            }
            minutes > 0 -> {
                finalTimerString.append(0)
                finalTimerString.append(minutes)
            }
            else -> {
                finalTimerString.append(0)
                finalTimerString.append(0)
            }
        }

        finalTimerString.append(":")

        when {
            seconds >= 10 -> {
                finalTimerString.append(seconds)
            }
            seconds > 0 -> {
                finalTimerString.append(0)
                finalTimerString.append(seconds)
            }
            else -> {
                finalTimerString.append(0)
                finalTimerString.append(0)
            }
        }

        return finalTimerString.toString()
    }

}